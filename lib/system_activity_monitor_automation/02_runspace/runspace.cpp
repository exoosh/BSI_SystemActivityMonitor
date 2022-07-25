#include "runspace.hpp"



namespace automation
{
	bool runspace::create(const std::wstring& file_path)
	{
		if (m_session_state_.load_from_file(file_path, L""))
		{

		}

		return true;
	}

	void runspace::start()
	{

	}

	void runspace::stop()
	{

	}

	void runspace::status()
	{

	}

	bool runspace::create_session()
	{
		for (auto& [session_tag, session_property] : m_session_state_.m_database.child_properties)
		{
			if (session_tag & 20000)
			{
				if (session_property->m_property.m_init)
				{
					for (auto it = session_property->m_property.m_data->begin(); it != session_property->m_property.m_data->end(); it++)
					{
						switch (it->first)
						{
							case 2000: //NAME = type string
							{
								auto name = std::get<std::wstring>(it->second);
								break;
							}
							case 2002: // KERNELSESSION = type bool
							{
								auto kernel_session = std::get<bool>(it->second);
								break;
							}
							case 2004: // MODE = type string
							{
								auto mode = std::get<std::wstring>(it->second);
								break;
							}
							case 2005: // BUFFERSIZE = type int
							{
								auto size = std::get<int>(it->second);
								break;
							}
							case 2006: // MINIMUMBUFFERS = type int
							{
								auto min = std::get<int>(it->second);
								break;
							}
							case 2007: // MAXIMUMBUFFERS = type int
							{
								auto max = std::get<int>(it->second);
								break;
							}
							case 2008: // FLUSHTIMER = type int
							{
								auto flush_timer = std::get<int>(it->second);
								break;
							}
							default:
							{
								break;
							}
						}



					}					
				}
			}	
		}




		
	}
}

