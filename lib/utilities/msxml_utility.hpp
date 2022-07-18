#pragma once
#include <system_error>
#include <set>
#include <sstream>

#include <combaseapi.h>

#import <msxml6.dll> exclude("ISequentialStream","_FILETIME")named_guids

namespace utility
{
	class msxml {

	public:
		msxml() {}
		msxml(DWORD dw_coinit_flag) { co_initialize(dw_coinit_flag); }

		~msxml();

	public:
		void co_initialize(DWORD dw_coinit_flag = COINIT_APARTMENTTHREADED);

		template<typename T>
		T create_instance();

		template<typename T>
		void load_document(const T& document_ptr, const std::wstring& file_name);

		template<typename T>
		MSXML2::IXMLDOMNodePtr get_single_node(const T& document_ptr, const std::wstring& query_string);

		template<typename T>
		MSXML2::IXMLDOMNodeListPtr get_multiple_nodes(const T& document_ptr, const std::wstring& query_string);

		void validate_document(
			const MSXML2::IXMLDOMDocument3Ptr& xml_document_ptr,
			const MSXML2::IXMLDOMDocument3Ptr& xsd_document_ptr,
			const MSXML2::IXMLDOMSchemaCollectionPtr& schema_collection_ptr,
			const std::wstring& namespace_uri = L"");

		MSXML2::IXMLDOMNamedNodeMapPtr get_attributes(const MSXML2::IXMLDOMNodePtr& node_ptr);
		MSXML2::IXMLDOMNodePtr get_named_item(const MSXML2::IXMLDOMNamedNodeMapPtr& node_map_ptr, const std::wstring& name);
		MSXML2::IXMLDOMNodeListPtr get_child_nodes(const MSXML2::IXMLDOMNodePtr& node_ptr);
		std::wstring get_text(const MSXML2::IXMLDOMNodePtr& node_ptr);
		std::wstring get_node_name(const MSXML2::IXMLDOMNodePtr& node_ptr);
		MSXML2::IXMLDOMNodePtr get_first_child(const MSXML2::IXMLDOMNodePtr& node_ptr);
		_variant_t get_node_value(const MSXML2::IXMLDOMNodePtr& node_ptr);
		std::set<int> split(const std::wstring& text);

	private:
		msxml(msxml const&) = delete;
		msxml& operator=(msxml const&) = delete;

	private:
		bool com_init_;
	};	
} /* namespace utility */


