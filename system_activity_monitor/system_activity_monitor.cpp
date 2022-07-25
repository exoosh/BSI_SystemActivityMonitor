#include <iostream>


#include "..\lib\system_activity_monitor_automation\03_session_state\session_state.hpp"


int wmain(int argc, wchar_t* argv[])
{
	automation::session_state ss;

	ss.load_from_file(L"C:\\Users\\dphillips\\source\\repos\\SystemActivityMonitor\\config\\NEW_SAMRecordingProfileExample.samp");

	std::cout << "";

	return 0;
}