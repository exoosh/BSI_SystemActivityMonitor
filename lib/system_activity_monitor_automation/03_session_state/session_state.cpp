#include "session_state.hpp"

#include <iostream>

namespace automation
{
	void session_state::load_from_file(const std::wstring& file_path)
	{
		//session_state_property session_list{ 20 };
		if (open_xml_file(file_path))
		{
			if (!parse_session_node())
				return;
			if (!parse_profile_node())
				return;
		}



		
	}

	bool session_state::open_xml_file(const std::wstring& file_path)
	{
		try {
			m_msxml_.co_initialize(COINIT_MULTITHREADED);
			m_xml_document_ptr_ = m_msxml_.create_instance<MSXML2::IXMLDOMDocument3Ptr>();
			m_msxml_.load_document(m_xml_document_ptr_, file_path);
		}
		catch (const std::system_error& se) {
			std::cout << "0x" << std::hex << se.code().value() << ":" << se.what() << std::endl;
			return false;
		}

		return true;
	}

	void session_state::validate_xml_file(const std::wstring& file_path)
	{

	}

	bool session_state::parse_session_node()
	{
		MSXML2::IXMLDOMNodePtr session_node{ nullptr };
		MSXML2::IXMLDOMNodePtr session_child_node{ nullptr };
		auto recording_session_node = m_msxml_.get_multiple_nodes(m_xml_document_ptr_, L"//SystemActivityMonitor//RecordingSessions//Session");
		if (recording_session_node != nullptr)
		{
			do 
			{
				session_node = nullptr;
				session_node = recording_session_node->nextNode();
				if (session_node != nullptr)
				{		
					session_state_property session{ 20000 };
					auto base_attribute_node = m_msxml_.get_attributes(session_node);
					if (base_attribute_node != nullptr)
					{			
						auto id = read_int_attribute_by_name(L"ID", base_attribute_node);
						if (id <= 0) { break; }
						session.tag += id;
													
						for (auto& [attribute_name, attribute_type, attribute_data_type] : session_state_common::session_node_attributes)
						{
							switch (attribute_data_type)
							{
								case session_state_common::data_type::WSTRING:
								{							
									if (attribute_type == session_state_common::attribute_type::NAME) 
									{
										auto name = read_wstring_attribute_by_name(attribute_name, base_attribute_node);
										if (!name.empty())
											session.append_property((2000 + (unsigned int)attribute_type), name);
									}																							
									else if (attribute_type == session_state_common::attribute_type::MODE)
									{
										auto mode = read_wstring_attribute_by_name(attribute_name, base_attribute_node);
										if(!mode.empty())
											session.append_property((2000 + (unsigned int)attribute_type), mode);
									}																	
									break;
								}
								case session_state_common::data_type::INT:
								{								
									break;
								}
								case session_state_common::data_type::BOOL:
								{
									if (attribute_type == session_state_common::attribute_type::KERNELSESSION) 
									{
										auto kernel_session = read_bool_attribute_by_name(attribute_name, base_attribute_node);
										if (kernel_session)
											session.append_property((2000 + (unsigned int)attribute_type), kernel_session);
									}									
									break;
								}
								default:
								{
								}
							}
						}
					}

					for (auto& [node_name, attribute_name, attribute_type, attribute_data_type] : session_state_common::session_child_nodes)
					{
						auto session_child_node = m_msxml_.get_single_node(session_node, node_name);
						if (session_child_node != nullptr)
						{
							auto child_attribute_node = m_msxml_.get_attributes(session_child_node);
							if (child_attribute_node != nullptr)
							{
								if (attribute_data_type == session_state_common::data_type::INT)
								{
									auto value = read_int_attribute_by_name(attribute_name, child_attribute_node);
									if (value > 0)
										session.append_property((2000 + (unsigned int)attribute_type), value);
								}
							}
						}
					}
					m_database_.connect_to(session);
				}
			} while (session_node != nullptr);
		}

		return true;
	}

	bool session_state::parse_profile_node()
	{
		MSXML2::IXMLDOMNodePtr next_profile_node{ nullptr };
		MSXML2::IXMLDOMNodePtr next_provider_node{ nullptr };

		try
		{
			auto profile_nodes = m_msxml_.get_multiple_nodes(m_xml_document_ptr_, L"//SystemActivityMonitor//RecordingProfiles//Profile");
			if (profile_nodes != nullptr)
			{
				do
				{
					next_profile_node = nullptr;
					next_profile_node = profile_nodes->nextNode();
					if (next_profile_node != nullptr)
					{
						unsigned int session_id{ 20000 };
						session_state_property profile{ 30000 };
						auto next_profile_node_attributes = m_msxml_.get_attributes(next_profile_node);
						if (next_profile_node_attributes != nullptr)
						{
							auto id = read_int_attribute_by_name(L"ID", next_profile_node_attributes);
							if (id <= 0) { break; }
							profile.tag += id; 
							session_id += id;
						}

						auto it = m_database_.child_properties.find(session_id);
						if (it != m_database_.child_properties.end())
						{
							auto provider_nodes = m_msxml_.get_child_nodes(next_profile_node);
							if (provider_nodes != nullptr)
							{
								unsigned int provider_index{ 0 };
								do
								{
									next_provider_node = nullptr;
									next_provider_node = provider_nodes->nextNode();
									if (next_provider_node != nullptr)
									{
										session_state_property provider{ 40000 + provider_index };
										parse_user_provider_node(provider, next_provider_node);
										profile.connect_to(provider);
										provider_index++;
									}
								} while (next_provider_node != nullptr);
							}

							it->second->connect_to(profile);
						}
					}
				} while (next_profile_node != nullptr);
			}
		}
		catch (const std::system_error& se)
		{
			std::cout << "0x" << std::hex << se.code().value() << ":" << se.what() << std::endl;
			return false;
		}

		return true;
	}

	void session_state::parse_user_provider_node(session_state_property& provider, const MSXML2::IXMLDOMNodePtr& provider_node)
	{
		if (provider_node != nullptr)
		{
			try
			{
				auto next_provider_node_attributes = m_msxml_.get_attributes(provider_node);
				if (next_provider_node_attributes != nullptr)
				{
					for (auto& [attribute_name, attribute_type, attribute_data_type] : session_state_common::provider_node_attributes)
					{
						switch (attribute_data_type)
						{
							case session_state_common::data_type::WSTRING:
							{

								if (attribute_type == session_state_common::attribute_type::NAME)
								{
									auto name = read_wstring_attribute_by_name(attribute_name, next_provider_node_attributes);
									if (!name.empty())
										provider.append_property((4000 + (unsigned int)attribute_type), name);
								}
								else if (attribute_type == session_state_common::attribute_type::GUID)
								{
									auto guid = read_wstring_attribute_by_name(attribute_name, next_provider_node_attributes);
									if (!guid.empty())
										provider.append_property((4000 + (unsigned int)attribute_type), guid);
								}
								break;
							}
							case session_state_common::data_type::INT:
							{

								break;
							}
							case session_state_common::data_type::BOOL:
							{
								if (attribute_type == session_state_common::attribute_type::RUNDOWN)
								{
									auto rundown = read_bool_attribute_by_name(attribute_name, next_provider_node_attributes);
									if (rundown)
										provider.append_property((4000 + (unsigned int)attribute_type), rundown);
								}
								break;
							}
							default:
							{
							}
						}
					}
				}
			}
			catch (const std::system_error& se)
			{
				std::cout << "0x" << std::hex << se.code().value() << ":" << se.what() << std::endl;
				throw;
			}
		}
	}

	void session_state::parse_kernel_provider_node()
	{

	}

	std::wstring session_state::read_wstring_attribute_by_name(const std::wstring& attribute_name, const MSXML2::IXMLDOMNamedNodeMapPtr& attribute_node)
	{
		if (attribute_node != nullptr && !attribute_name.empty())
		{
			auto attribute = m_msxml_.get_named_item(attribute_node, attribute_name);
			//auto attribute = attribute_node->getNamedItem(attribute_name.c_str());
			if (attribute != nullptr)
				return m_msxml_.get_text(attribute);
		}

		return L"";
	}
	
	int session_state::read_int_attribute_by_name(const std::wstring& attribute_name, const MSXML2::IXMLDOMNamedNodeMapPtr& attribute_node)
	{
		if (attribute_node != nullptr && !attribute_name.empty())
		{
			auto attribute = m_msxml_.get_named_item(attribute_node, attribute_name);
			//auto attribute = attribute_node->getNamedItem(attribute_name.c_str());
			if (attribute != nullptr)
			{
				auto value = m_msxml_.get_node_value(attribute);
				if (SysStringLen(value.bstrVal) != 0)
					return value.operator int();
			}
		}

		return 0;
	}

	bool session_state::read_bool_attribute_by_name(const std::wstring& attribute_name, const MSXML2::IXMLDOMNamedNodeMapPtr& attribute_node)
	{
		if (attribute_node != nullptr && !attribute_name.empty())
		{
			auto attribute = m_msxml_.get_named_item(attribute_node, attribute_name);
			//auto attribute = attribute_node->getNamedItem(attribute_name.c_str());
			if (attribute != nullptr)
			{
				auto value = m_msxml_.get_node_value(attribute);
				if (SysStringLen(value.bstrVal) != 0)
					return value.operator bool();
			}
		}

		return false;
	}
}