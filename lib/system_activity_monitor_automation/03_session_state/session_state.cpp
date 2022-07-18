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
			if (!parse_kernel_session_node())
				return;
		}



		/*session_state_property session1{ 21 };
		session_state_property session2{ 22 };

		session_state_property provider_list1{ 30 };
		session_state_property provider_list2{ 30 };

		session_state_property provider11{ 31 };		
		session_state_property provider12{ 32 };
		session_state_property provider13{ 33 };

		session_state_property provider21{ 31 };
		session_state_property provider22{ 32 };
		session_state_property provider23{ 33 };
		
		provider_list1.connect_to(provider11);
		provider_list1.connect_to(provider12);
		provider_list1.connect_to(provider13);

		provider_list2.connect_to(provider21);
		provider_list2.connect_to(provider22);
		provider_list2.connect_to(provider23);

		session1.connect_to(provider_list1);
		session2.connect_to(provider_list2);

		m_database_.connect_to(session1);
		m_database_.connect_to(session2);*/
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
					auto base_attribute_node = m_msxml_.get_attributes(session_node);
					if (base_attribute_node != nullptr)
					{
						for (auto& [attribute_name, type] : session_state_common::base_session_attributes)
						{
							switch (type)
							{
							case session_state_common::data_type::WSTRING:
							{
								auto a1 = read_wstr_attribute_by_name(attribute_name, base_attribute_node);
								break;
							}
							case session_state_common::data_type::INT:
							{
								auto a2 = read_int_attribute_by_name(attribute_name, base_attribute_node);
								break;
							}
							case session_state_common::data_type::BOOL:
							{
								auto a3 = read_bool_attribute_by_name(attribute_name, base_attribute_node);
								break;
							}
							default:
							{
							}
							}
						}			
					}

					for (auto& [node_name, type] : session_state_common::session_child_nodes)
					{
						auto session_child_node = m_msxml_.get_single_node(session_node, node_name);
						if (session_child_node != nullptr)
						{
							auto child_attribute_node = m_msxml_.get_attributes(session_child_node);
							if (child_attribute_node != nullptr)
							{
								if (type == session_state_common::data_type::INT)
								{
									auto value = read_int_attribute_by_name(L"Value", child_attribute_node);
									std::wcout << node_name << ":" << value << std::endl;
									//if (value != 0) { session_properties[child_node.first] = value; }
								}
							}
						}
					}					
				}
			} while (session_node != nullptr);
		}

		return true;
	}

	bool session_state::parse_kernel_session_node()
	{
		return true;
	}

	void session_state::parse_user_provider_node()
	{

	}

	void session_state::parse_kernel_provider_node()
	{

	}

	std::wstring session_state::read_wstr_attribute_by_name(const std::wstring& attribute_name, const MSXML2::IXMLDOMNamedNodeMapPtr& attribute_node)
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