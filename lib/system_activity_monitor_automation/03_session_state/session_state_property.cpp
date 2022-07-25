#include "session_state.hpp"


namespace automation
{ 
    session_state_property::session_state_property(unsigned int tag)
        : tag(tag)
    {
        static int id = 1;
        this->id = id++;
    }

    //template<typename T>
    //void session_state_property::append_property(unsigned int tag, T value)
    //{
    //    if (m_property_.m_init == false)
    //    {
    //        m_property_.m_init = true;
    //        m_property_.m_data = new std::map<unsigned int, std::variant<int, std::wstring, bool>>();
    //    }

    //    //std::variant<int, std::wstring>

    //    auto f = std::variant<int, std::wstring>(value);
    //    m_property_.m_data->operator[](tag) = value;
    //    std::cout << "stop" << std::endl;
    //    //m_data_.m_concreat_data[tag] = std::variant<int, std::wstring>(value);
    //}

    void session_state_property::connect_to(session_state_property& other)
    {
        for (auto& parent : *this)
        {
            for (auto& child : other)
            {
                parent.child_properties.emplace(child.tag, new session_state_property(child));
                child.parent_properties.emplace(parent.tag, &parent);
            }
        }
    }

    session_state_property* session_state_property::begin()
    {
        return this;
    }
    session_state_property* session_state_property::end()
    {
        return this + 1;
    }  
}
