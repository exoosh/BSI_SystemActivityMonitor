#pragma once
#include <vector>
#include <string>
#include <tuple>
#include <typeinfo>

namespace automation
{
	namespace session_state_common
	{
		enum class tag
		{
			LIST,

		};

		enum class data_type
		{
			WSTRING,
			INT,
			BOOL
		};

		enum class attribute_type
		{
			NAME,
			ID,
			KERNELSESSION,
			KERNELPROVIDER,
			MODE,
			BUFFERSIZE,
			MINIMUMBUFFERS,
			MAXIMUMBUFFERS,
			FLUSHTIMER,
			GUID,
			LEVEL,
			RUNDOWN,
			ALL,
			ANY
		};

		const std::vector<std::tuple<std::wstring, attribute_type, data_type>> session_node_attributes
		{
			std::make_tuple(L"Name", attribute_type::NAME, data_type::WSTRING),
			std::make_tuple(L"ID", attribute_type::ID, data_type::INT),
			std::make_tuple(L"KernelSession", attribute_type::KERNELSESSION, data_type::BOOL),
			std::make_tuple(L"Mode", attribute_type::MODE, data_type::WSTRING)
		};

		const std::vector<std::tuple<std::wstring, std::wstring, attribute_type, data_type>> session_child_nodes
		{
			std::make_tuple(L"BufferSize", L"Value", attribute_type::BUFFERSIZE, data_type::INT),
			std::make_tuple(L"MinimumBuffers", L"Value", attribute_type::MINIMUMBUFFERS, data_type::INT),
			std::make_tuple(L"MaximumBuffers", L"Value", attribute_type::MAXIMUMBUFFERS, data_type::INT),
			std::make_tuple(L"FlushTimer", L"Value", attribute_type::FLUSHTIMER, data_type::INT)
		};

		const std::vector<std::tuple<std::wstring, attribute_type, data_type>> provider_node_attributes
		{
			std::make_tuple(L"Name", attribute_type::NAME, data_type::WSTRING),
			std::make_tuple(L"Guid", attribute_type::GUID, data_type::WSTRING),
			std::make_tuple(L"Level", attribute_type::LEVEL, data_type::INT),
			std::make_tuple(L"Rundown", attribute_type::RUNDOWN, data_type::BOOL)
		};
	}
}