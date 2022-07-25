#pragma once
#include <string>

#include "00_common/session_state_common.h"
#include "session_state_property.hpp"

#include "..\..\utilities\msxml_utility.hpp"

namespace automation
{
	class session_state
	{
	public:
		void load_from_file(const std::wstring& file_path);
		

	protected:



	private:
		bool open_xml_file(const std::wstring& file_path);
		void validate_xml_file(const std::wstring& file_path);

		bool parse_session_node();
		
		bool parse_profile_node();
		void parse_user_provider_node(session_state_property& provider, const MSXML2::IXMLDOMNodePtr& next_profile_node);
		void parse_kernel_provider_node();

		bool parse_kernel_session_node();
		

	



		std::wstring read_wstring_attribute_by_name(const std::wstring& attribute_name, const MSXML2::IXMLDOMNamedNodeMapPtr& attribute_node);
		int read_int_attribute_by_name(const std::wstring& attribute_name, const MSXML2::IXMLDOMNamedNodeMapPtr& attribute_node);
		bool read_bool_attribute_by_name(const std::wstring& attribute_name, const MSXML2::IXMLDOMNamedNodeMapPtr& attribute_node);

		

		//inline bool session_state_base::get_attr_bool_val_by_name(const std::wstring& attr_name, const MSXML2::IXMLDOMNamedNodeMapPtr& attr_map_ptr)
		//{
		//	if (attr_map_ptr != nullptr && !attr_name.empty())
		//	{
		//		auto attr_ptr = attr_map_ptr->getNamedItem(attr_name.c_str());
		//		if (attr_ptr != nullptr)
		//		{
		//			auto value = msxml_.get_node_value(attr_ptr);
		//			if (SysStringLen(value.bstrVal) != 0)
		//			{
		//				return value.operator bool();
		//			}
		//		}

		//	}

		//	return false;
		//}

		//inline unsigned char session_state_base::get_attr_uchar_val_by_name(const std::wstring& attr_name, const MSXML2::IXMLDOMNamedNodeMapPtr& attr_map_ptr)
		//{
		//	if (attr_map_ptr != nullptr && !attr_name.empty())
		//	{
		//		auto attr_ptr = attr_map_ptr->getNamedItem(attr_name.c_str());
		//		if (attr_ptr != nullptr)
		//		{
		//			auto value = msxml_.get_node_value(attr_ptr);
		//			if (SysStringLen(value.bstrVal) != 0)
		//			{
		//				return value.operator unsigned char();
		//			}
		//		}
		//	}

		//	return 0;
		//}

		//inline unsigned long long session_state_base::get_attr_ulonglong_val_by_name(const std::wstring& attr_name, const MSXML2::IXMLDOMNamedNodeMapPtr& attr_map_ptr)
		//{
		//	if (attr_map_ptr != nullptr && !attr_name.empty())
		//	{
		//		auto attr_ptr = attr_map_ptr->getNamedItem(attr_name.c_str());
		//		if (attr_ptr != nullptr)
		//		{
		//			auto value = msxml_.get_text(attr_ptr);
		//			if (!value.empty()) {
		//				return  std::wcstoull(value.c_str(), 0, 16);
		//			}
		//		}
		//	}

		//	return 0;
		//}



		utility::msxml m_msxml_;
		MSXML2::IXMLDOMDocument3Ptr m_xml_document_ptr_;
		session_state_property m_database_{ 10 }; //tag database
	};
}



