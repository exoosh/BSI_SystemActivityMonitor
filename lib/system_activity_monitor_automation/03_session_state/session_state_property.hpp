#pragma once
#include <iostream>
#include <string>
#include <map>
#include <variant>

namespace automation
{  
    class session_state_property
    {
    public:
        session_state_property(unsigned int tag);

        template<typename T>
        void append_property(unsigned int tag, T value)
        {
            if (m_property_.m_init == false)
            {
                m_property_.m_init = true;
                m_property_.m_data = new std::map<unsigned int, std::variant<int, std::wstring, bool>>();
            }

            //std::variant<int, std::wstring>

            auto f = std::variant<int, std::wstring>(value);
            m_property_.m_data->operator[](tag) = value;
            std::cout << "stop" << std::endl;
            //m_data_.m_concreat_data[tag] = std::variant<int, std::wstring>(value);
        }

        void remove_property(unsigned int tag);
        void connect_to(session_state_property& other);

        //TODO: fix memory leak
        std::map<unsigned int, session_state_property*> parent_properties, child_properties;
        unsigned int id;
        unsigned int tag;

    protected:

    private:
        session_state_property* begin();
        session_state_property* end();

        struct property
        {
            property() : m_init(false) {}
            ~property() { if(!m_data) delete m_data; }

            bool m_init;
            std::map<unsigned int, std::variant<int, std::wstring, bool>>* m_data;
        }m_property_;
    };
    
}










