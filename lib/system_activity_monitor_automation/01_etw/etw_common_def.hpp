#pragma once
#include <string>

namespace automation
{
	namespace etw_common
	{
		struct session
		{
			std::wstring id;
			std::wstring name;
			int flush_time{ 0 };
			int buffer_size{ 0 };
			int maximum_buffers{ 0 };
			int minimum_buffers{ 0 };
		};

		struct provider
		{
			std::wstring name;
			std::wstring guid;
			unsigned char level{ 0 };
			unsigned long long any{ 0 };
			unsigned long long all{ 0 };
			bool rundown_enabled{ false };
			bool is_kernel{ false };
		};
	}
}
