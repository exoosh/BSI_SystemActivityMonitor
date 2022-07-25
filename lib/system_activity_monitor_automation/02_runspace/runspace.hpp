#pragma once

#include "..\03_session_state\session_state.hpp"

namespace automation
{
	class runspace
	{
	public:
		bool create(const std::wstring& file_path);
		void start();
		void stop();
		void status();

		unsigned int m_id;
	protected:
	private:
		bool create_session();
		//std::vector<int> get_session_ids();
			

		session_state m_session_state_;

	};
}


