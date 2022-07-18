#pragma once
#include <vector>
#include <string>
#include <tuple>
#include <typeinfo>

namespace automation
{
	namespace session_state_common
	{
		enum class data_type
		{
			WSTRING,
			INT,
			BOOL
		};

		const std::vector<std::tuple<std::wstring, data_type>> base_session_attributes
		{
			std::make_tuple(L"Name", data_type::WSTRING),
			std::make_tuple(L"ID", data_type::INT),
			std::make_tuple(L"KernelSession", data_type::BOOL),
			std::make_tuple(L"Mode", data_type::WSTRING)
		};

		const std::vector<std::tuple<std::wstring, data_type>> session_child_nodes
		{
			std::make_tuple(L"BufferSize", data_type::INT),
			std::make_tuple(L"MinimumBuffers", data_type::INT),
			std::make_tuple(L"MaximumBuffers", data_type::INT),
			std::make_tuple(L"FlushTimer", data_type::INT)
		};
		

		//assert(ti1.hash_code() == ti2.hash_code());
		/*const std::vector<std::tuple<std::wstring, std::wstring, std::wstring>> session_attributes
		{
			std::make_tuple(L"sam_user_session", L"//SystemActivityMonitor//Provider//EventProviders", L"EventProvider"),
			std::make_tuple(L"sam_kernel_session", L"//SystemActivityMonitor//Provider//SystemProviders", L"SystemProvider")
		};

		const std::vector<std::tuple<std::wstring, std::wstring, std::wstring>> base_provider_attributes
		{
			std::make_tuple(L"sam_user_session", L"//SystemActivityMonitor//Provider//EventProviders", L"EventProvider"),
			std::make_tuple(L"sam_kernel_session", L"//SystemActivityMonitor//Provider//SystemProviders", L"SystemProvider")
		};

		const std::vector<std::tuple<std::wstring, std::wstring, std::wstring>> provider_attributes
		{
			std::make_tuple(L"sam_user_session", L"//SystemActivityMonitor//Provider//EventProviders", L"EventProvider"),
			std::make_tuple(L"sam_kernel_session", L"//SystemActivityMonitor//Provider//SystemProviders", L"SystemProvider")
		};*/

		

	}
}