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
        void append_property(unsigned int tag, T value);

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
            std::map<unsigned int, std::variant<int, std::wstring>>* m_data;
        }m_property_;
    };
    
}










