#include "msxml_utility.hpp"

namespace utility
{
	/**
	*
	* implementation
	* ------------------------------------------------------------------------
	*/
	void msxml::co_initialize(DWORD dw_coinit_flag /* = COINIT_APARTMENTTHREADED */)
	{
		// initialize the COM library on the current thread
		HRESULT hr = ::CoInitializeEx(nullptr, dw_coinit_flag);
		if (FAILED(hr)) {
			auto ec = std::error_code(hr, std::system_category());
			throw std::system_error(ec, "CoInitializeEx() failed");
		}

		com_init_ = true;
	}

	//inline msxml::msxml(DWORD dw_coinit_flag /* = COINIT_APARTMENTTHREADED */)
	//	: com_init_(false)
	//{
	//	// initialize the COM library on the current thread
	//	HRESULT hr = ::CoInitializeEx(nullptr, dw_coinit_flag);
	//	if (FAILED(hr)) {
	//		auto ec = std::error_code(hr, std::system_category());
	//		throw std::system_error(ec, "CoInitializeEx() failed");
	//	}

	//	com_init_ = true;
	//}

	msxml::~msxml() {
		// free the COM library.
		if (com_init_)
			::CoUninitialize();
	}

	template<>
	MSXML2::IXMLDOMDocumentPtr msxml::create_instance<MSXML2::IXMLDOMDocumentPtr>() {

		MSXML2::IXMLDOMDocumentPtr xml_document;
		//std::shared_ptr<MSXML2::IXMLDOMDocument2> xml_document_ptr;
		//__uuidof(MSXML2::DOMDocument60), NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(ppDoc)
		HRESULT hr = xml_document.CreateInstance(__uuidof(MSXML2::DOMDocument60), NULL, CLSCTX_INPROC_SERVER);
		//HRESULT hr = ::CreateInstance(__uuidof(MSXML2::DOMDocument60), NULL, CLSCTX_INPROC_SERVER);
		if (FAILED(hr)) {
			auto ec = std::error_code(hr, std::system_category());
			throw std::system_error(ec, "MSXML2::IXMLDOMDocumentPtr 'CreateInstance()' failed");
		}

		return xml_document;

	}

	template<>
	MSXML2::IXMLDOMDocument2Ptr msxml::create_instance<MSXML2::IXMLDOMDocument2Ptr>() {

		MSXML2::IXMLDOMDocument2Ptr xml_document;
		//std::shared_ptr<MSXML2::IXMLDOMDocument2> xml_document_ptr;
		//__uuidof(MSXML2::DOMDocument60), NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(ppDoc)
		HRESULT hr = xml_document.CreateInstance(__uuidof(MSXML2::DOMDocument60), NULL, CLSCTX_INPROC_SERVER);
		//HRESULT hr = ::CreateInstance(__uuidof(MSXML2::DOMDocument60), NULL, CLSCTX_INPROC_SERVER);
		if (FAILED(hr)) {
			auto ec = std::error_code(hr, std::system_category());
			throw std::system_error(ec, "MSXML2::IXMLDOMDocument2Ptr 'CreateInstance()' failed");
		}

		return xml_document;

	}

	template<>
	MSXML2::IXMLDOMDocument3Ptr msxml::create_instance<MSXML2::IXMLDOMDocument3Ptr>() {

		MSXML2::IXMLDOMDocument3Ptr xml_document;
		//std::shared_ptr<MSXML2::IXMLDOMDocument2> xml_document_ptr;
		//__uuidof(MSXML2::DOMDocument60), NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(ppDoc)
		HRESULT hr = xml_document.CreateInstance(__uuidof(MSXML2::DOMDocument60), NULL, CLSCTX_INPROC_SERVER);
		//HRESULT hr = ::CreateInstance(__uuidof(MSXML2::DOMDocument60), NULL, CLSCTX_INPROC_SERVER);
		if (FAILED(hr)) {
			auto ec = std::error_code(hr, std::system_category());
			throw std::system_error(ec, "MSXML2::IXMLDOMDocument3Ptr 'CreateInstance()' failed");
		}

		return xml_document;

	}

	template<>
	MSXML2::IXMLDOMSchemaCollectionPtr msxml::create_instance<MSXML2::IXMLDOMSchemaCollectionPtr>()
	{
		MSXML2::IXMLDOMSchemaCollectionPtr xml_document;
		//std::shared_ptr<MSXML2::IXMLDOMDocument2> xml_document_ptr;
		//__uuidof(MSXML2::DOMDocument60), NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(ppDoc)
		HRESULT hr = xml_document.CreateInstance(__uuidof(MSXML2::XMLSchemaCache60), NULL, CLSCTX_INPROC_SERVER);
		//HRESULT hr = ::CreateInstance(__uuidof(MSXML2::DOMDocument60), NULL, CLSCTX_INPROC_SERVER);
		if (FAILED(hr))
		{
			auto ec = std::error_code(hr, std::system_category());
			throw std::system_error(ec, "MSXML2::IXMLDOMSchemaCollectionPtr 'CreateInstance()' failed");
		}

		return xml_document;
	}

	template<>
	void msxml::load_document<MSXML2::IXMLDOMDocumentPtr>(const MSXML2::IXMLDOMDocumentPtr& document_ptr, const std::wstring& file_name)
	{
		if (document_ptr == nullptr) { throw std::invalid_argument("'document_ptr' cannot be nullptr"); }

		document_ptr->async = VARIANT_FALSE;
		document_ptr->validateOnParse = VARIANT_FALSE;

		if (document_ptr->load(file_name.c_str()) != VARIANT_TRUE)
		{
			HRESULT hr = document_ptr->parseError->errorCode;
			auto ec = std::error_code(hr, std::system_category());
			throw std::system_error(ec, "MSXML2::IXMLDOMDocumentPtr 'load()' failed");
		}
	}

	template<>
	void msxml::load_document<MSXML2::IXMLDOMDocument2Ptr>(const MSXML2::IXMLDOMDocument2Ptr& document_ptr, const std::wstring& file_name)
	{
		if (document_ptr == nullptr) { throw std::invalid_argument("'document_ptr' cannot be nullptr"); }

		document_ptr->async = VARIANT_FALSE;
		document_ptr->validateOnParse = VARIANT_FALSE;

		if (document_ptr->load(file_name.c_str()) != VARIANT_TRUE)
		{
			HRESULT hr = document_ptr->parseError->errorCode;
			auto ec = std::error_code(hr, std::system_category());
			throw std::system_error(ec, "MSXML2::IXMLDOMDocument2Ptr 'load()' failed");
		}
	}

	template<>
	void msxml::load_document<MSXML2::IXMLDOMDocument3Ptr>(const MSXML2::IXMLDOMDocument3Ptr& document_ptr, const std::wstring& file_name)
	{
		if (document_ptr == nullptr) { throw std::invalid_argument("'document_ptr' cannot be nullptr"); }

		document_ptr->async = VARIANT_FALSE;
		document_ptr->validateOnParse = VARIANT_FALSE;

		if (document_ptr->load(file_name.c_str()) != VARIANT_TRUE)
		{
			HRESULT hr = document_ptr->parseError->errorCode;
			auto ec = std::error_code(hr, std::system_category());
			throw std::system_error(ec, "MSXML2::IXMLDOMDocument3Ptr 'load()' failed");
		}
	}

	/*inline void xml::add_schema_collection(const MSXML2::IXMLDOMSchemaCollectionPtr& schema_collection_ptr, const MSXML2::IXMLDOMDocument3Ptr& document_ptr, const std::wstring& namespace_uri) {

		if (document_ptr == nullptr) {
			throw std::invalid_argument("'document_ptr' cannot be nullptr");
		}

		HRESULT hr = schema_collection_ptr->add(namespace_uri.c_str(), document_ptr.GetInterfacePtr());

		if (FAILED(hr)) {
			auto ec = std::error_code(hr, std::system_category());
			throw std::system_error(ec, "MSXML2::IXMLDOMSchemaCollectionPtr 'add()' failed");
		}

	}*/

	void msxml::validate_document(
		const MSXML2::IXMLDOMDocument3Ptr& xml_document_ptr,
		const MSXML2::IXMLDOMDocument3Ptr& xsd_document_ptr,
		const MSXML2::IXMLDOMSchemaCollectionPtr& schema_collection_ptr,
		const std::wstring& namespace_uri /* = L"" */)
	{
		if (xml_document_ptr == nullptr) { throw std::invalid_argument("'xml_document_ptr' cannot be nullptr"); }

		if (xsd_document_ptr == nullptr) { throw std::invalid_argument("'xsd_document_ptr' cannot be nullptr"); }

		HRESULT hr = schema_collection_ptr->add(namespace_uri.c_str(), xsd_document_ptr.GetInterfacePtr());

		if (FAILED(hr))
		{
			auto ec = std::error_code(hr, std::system_category());
			throw std::system_error(ec, "MSXML2::IXMLDOMSchemaCollectionPtr 'add()' failed");
		}

		xml_document_ptr->schemas = schema_collection_ptr.GetInterfacePtr();
		MSXML2::IXMLDOMParseErrorPtr parse_error_ptr = xml_document_ptr->validate();

		if (parse_error_ptr->errorCode != 0)
		{
			auto ec = std::error_code(parse_error_ptr->errorCode, std::system_category());
			auto message = parse_error_ptr->Getreason();
			throw std::system_error(ec, message);
		}
	}

	template<>
	MSXML2::IXMLDOMNodePtr msxml::get_single_node<MSXML2::IXMLDOMDocumentPtr>(const MSXML2::IXMLDOMDocumentPtr& document_ptr, const std::wstring& query_string)
	{
		if (document_ptr == nullptr) { throw std::invalid_argument("'node_ptr' cannot be nullptr"); }

		MSXML2::IXMLDOMNodePtr node_ptr;
		HRESULT hr = document_ptr->raw_selectSingleNode((wchar_t*)query_string.c_str(), &node_ptr);

		if (FAILED(hr))
		{
			auto ec = std::error_code(hr, std::system_category());
			throw std::system_error(ec, "MSXML2::IXMLDOMNodePtr 'raw_selectSingleNode()' failed");
		}

		return node_ptr;
	}

	template<>
	MSXML2::IXMLDOMNodePtr msxml::get_single_node<MSXML2::IXMLDOMDocument2Ptr>(const MSXML2::IXMLDOMDocument2Ptr& document_ptr, const std::wstring& query_string)
	{
		if (document_ptr == nullptr) { throw std::invalid_argument("'node_ptr' cannot be nullptr"); }

		MSXML2::IXMLDOMNodePtr node_ptr;
		HRESULT hr = document_ptr->raw_selectSingleNode((wchar_t*)query_string.c_str(), &node_ptr);

		if (FAILED(hr))
		{
			auto ec = std::error_code(hr, std::system_category());
			throw std::system_error(ec, "MSXML2::IXMLDOMNodePtr 'raw_selectSingleNode()' failed");
		}

		return node_ptr;
	}

	template<>
	MSXML2::IXMLDOMNodePtr msxml::get_single_node<MSXML2::IXMLDOMDocument3Ptr>(const MSXML2::IXMLDOMDocument3Ptr& document_ptr, const std::wstring& query_string)
	{
		if (document_ptr == nullptr) { throw std::invalid_argument("'node_ptr' cannot be nullptr"); }

		MSXML2::IXMLDOMNodePtr node_ptr;
		HRESULT hr = document_ptr->raw_selectSingleNode((wchar_t*)query_string.c_str(), &node_ptr);

		if (FAILED(hr))
		{
			auto ec = std::error_code(hr, std::system_category());
			throw std::system_error(ec, "MSXML2::IXMLDOMNodePtr 'raw_selectSingleNode()' failed");
		}

		return node_ptr;
	}

	template<>
	MSXML2::IXMLDOMNodePtr msxml::get_single_node<MSXML2::IXMLDOMNodePtr>(const MSXML2::IXMLDOMNodePtr& node_ptr, const std::wstring& query_string)
	{
		if (node_ptr == nullptr) { throw std::invalid_argument("'node_ptr' cannot be nullptr"); }

		MSXML2::IXMLDOMNodePtr _node_ptr;
		HRESULT hr = node_ptr->raw_selectSingleNode((wchar_t*)query_string.c_str(), &_node_ptr);

		if (FAILED(hr))
		{
			auto ec = std::error_code(hr, std::system_category());
			throw std::system_error(ec, "MSXML2::IXMLDOMNodePtr 'raw_selectSingleNode()' failed");
		}

		return _node_ptr;
	}

	template<>
	MSXML2::IXMLDOMNodeListPtr msxml::get_multiple_nodes<MSXML2::IXMLDOMDocumentPtr>(const MSXML2::IXMLDOMDocumentPtr& document_ptr, const std::wstring& query_string)
	{
		if (document_ptr == nullptr) { throw std::invalid_argument("'node_ptr' cannot be nullptr"); }

		MSXML2::IXMLDOMNodeListPtr node_ptr;
		HRESULT hr = document_ptr->raw_selectNodes((wchar_t*)query_string.c_str(), &node_ptr);

		if (FAILED(hr))
		{
			auto ec = std::error_code(hr, std::system_category());
			throw std::system_error(ec, "MSXML2::IXMLDOMNodePtr 'raw_selectSingleNode()' failed");
		}

		return node_ptr;
	}

	template<>
	MSXML2::IXMLDOMNodeListPtr msxml::get_multiple_nodes<MSXML2::IXMLDOMDocument2Ptr>(const MSXML2::IXMLDOMDocument2Ptr& document_ptr, const std::wstring& query_string)
	{
		if (document_ptr == nullptr) { throw std::invalid_argument("'node_ptr' cannot be nullptr"); }

		MSXML2::IXMLDOMNodeListPtr node_ptr;
		HRESULT hr = document_ptr->raw_selectNodes((wchar_t*)query_string.c_str(), &node_ptr);

		if (FAILED(hr))
		{
			auto ec = std::error_code(hr, std::system_category());
			throw std::system_error(ec, "MSXML2::IXMLDOMNodePtr 'raw_selectSingleNode()' failed");
		}

		return node_ptr;
	}

	template<>
	MSXML2::IXMLDOMNodeListPtr msxml::get_multiple_nodes<MSXML2::IXMLDOMDocument3Ptr>(const MSXML2::IXMLDOMDocument3Ptr& document_ptr, const std::wstring& query_string)
	{

		if (document_ptr == nullptr) { throw std::invalid_argument("'node_ptr' cannot be nullptr"); }

		MSXML2::IXMLDOMNodeListPtr node_ptr;
		HRESULT hr = document_ptr->raw_selectNodes((wchar_t*)query_string.c_str(), &node_ptr);

		if (FAILED(hr))
		{
			auto ec = std::error_code(hr, std::system_category());
			throw std::system_error(ec, "MSXML2::IXMLDOMNodePtr 'raw_selectSingleNode()' failed");
		}

		return node_ptr;
	}

	template<>
	MSXML2::IXMLDOMNodeListPtr msxml::get_multiple_nodes<MSXML2::IXMLDOMNodePtr>(const MSXML2::IXMLDOMNodePtr& node_ptr, const std::wstring& query_string)
	{
		if (node_ptr == nullptr) { throw std::invalid_argument("'node_ptr' cannot be nullptr"); }

		MSXML2::IXMLDOMNodeListPtr _node_ptr;
		HRESULT hr = node_ptr->raw_selectNodes((wchar_t*)query_string.c_str(), &_node_ptr);

		if (FAILED(hr))
		{
			auto ec = std::error_code(hr, std::system_category());
			throw std::system_error(ec, "MSXML2::IXMLDOMNodePtr 'raw_selectSingleNode()' failed");
		}

		return _node_ptr;
	}

	MSXML2::IXMLDOMNamedNodeMapPtr msxml::get_attributes(const MSXML2::IXMLDOMNodePtr& node_ptr)
	{
		if (node_ptr == nullptr) { throw std::invalid_argument("'node_ptr' cannot be nullptr"); }

		MSXML2::IXMLDOMNamedNodeMapPtr node_map_ptr;
		HRESULT hr = node_ptr->get_attributes(&node_map_ptr);

		if (FAILED(hr))
		{
			auto ec = std::error_code(hr, std::system_category());
			throw std::system_error(ec, "MSXML2::IXMLDOMNodePtr 'get_attributes()' failed");
		}

		return node_map_ptr;
	}

	MSXML2::IXMLDOMNodePtr msxml::get_named_item(const MSXML2::IXMLDOMNamedNodeMapPtr& node_map_ptr, const std::wstring& name)
	{
		if (node_map_ptr == nullptr) { throw std::invalid_argument("'node_map_ptr' cannot be nullptr"); }

		MSXML2::IXMLDOMNodePtr node_ptr;
		HRESULT hr = node_map_ptr->raw_getNamedItem((wchar_t*)name.c_str(), &node_ptr);

		if (FAILED(hr))
		{
			auto ec = std::error_code(hr, std::system_category());
			throw std::system_error(ec, "MSXML2::IXMLDOMNamedNodeMapPtr 'raw_getNamedItem()' failed");
		}

		return node_ptr;
	}

	std::wstring msxml::get_text(const MSXML2::IXMLDOMNodePtr& node_ptr)
	{
		if (node_ptr == nullptr) { throw std::invalid_argument("'node_ptr' cannot be nullptr"); }

		BSTR bstr = NULL;
		HRESULT hr = node_ptr->get_text(&bstr);

		if (FAILED(hr))
		{
			auto ec = std::error_code(hr, std::system_category());
			throw std::system_error(ec, "MSXML2::IXMLDOMNodePtr 'get_text()' failed");
		}

		return std::wstring(bstr);
	}

	_variant_t msxml::get_node_value(const MSXML2::IXMLDOMNodePtr& node_ptr)
	{
		if (node_ptr == nullptr) { throw std::invalid_argument("'node_ptr' cannot be nullptr"); }

		_variant_t value;
		HRESULT hr = node_ptr->get_nodeValue(&value);

		if (FAILED(hr))
		{
			auto ec = std::error_code(hr, std::system_category());
			throw std::system_error(ec, "MSXML2::IXMLDOMNodePtr 'get_text()' failed");
		}

		return value;
	}

	std::wstring msxml::get_node_name(const MSXML2::IXMLDOMNodePtr& node_ptr)
	{
		if (node_ptr == nullptr) { throw std::invalid_argument("'node_ptr' cannot be nullptr"); }

		BSTR bstr = NULL;
		HRESULT hr = node_ptr->get_nodeName(&bstr);

		if (FAILED(hr))
		{
			auto ec = std::error_code(hr, std::system_category());
			throw std::system_error(ec, "MSXML2::IXMLDOMNodePtr 'get_nodeName()' failed");
		}

		return std::wstring(bstr);
	}

	MSXML2::IXMLDOMNodePtr msxml::get_first_child(const MSXML2::IXMLDOMNodePtr& node_ptr)
	{
		if (node_ptr == nullptr) { throw std::invalid_argument("'node_ptr' cannot be nullptr"); }

		MSXML2::IXMLDOMNodePtr _node_ptr;
		HRESULT hr = node_ptr->get_firstChild(&_node_ptr);

		if (FAILED(hr))
		{
			auto ec = std::error_code(hr, std::system_category());
			throw std::system_error(ec, "MSXML2::IXMLDOMNodePtr 'get_firstChild()' failed");
		}

		return _node_ptr;
	}

	MSXML2::IXMLDOMNodeListPtr msxml::get_child_nodes(const MSXML2::IXMLDOMNodePtr& node_ptr)
	{
		if (node_ptr == nullptr) { throw std::invalid_argument("'node_ptr' cannot be nullptr"); }

		MSXML2::IXMLDOMNodeListPtr node_List_ptr;
		HRESULT hr = node_ptr->get_childNodes(&node_List_ptr);

		if (FAILED(hr))
		{
			auto ec = std::error_code(hr, std::system_category());
			throw std::system_error(ec, "MSXML2::IXMLDOMNodePtr 'get_childNodes()' failed");
		}

		return node_List_ptr;
	}

	std::set<int> msxml::split(const std::wstring& text)
	{
		std::set<int> ids;
		std::wstring id;
		std::wstringstream wstream(text);
		wchar_t space_char = ' ';

		while (std::getline(wstream, id, space_char))
		{
			id.erase(std::remove_if(id.begin(), id.end(), ispunct), id.end());
			if (!id.empty())
			{
				auto i = std::stoi(id);
				ids.insert(i);
			}
		}

		return ids;
	}



}