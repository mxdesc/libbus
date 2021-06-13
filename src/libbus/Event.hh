#pragma once

#include <string>

namespace libbus{
class Event{

    public:

        Event(std::string data, int id, std::string name)
        {

            this->data_ = data;
            this->id_ = id;
            this->name_ = name;

        }


        std::string get_name()
        {
            return name_;
        }

        std::string get_data()
        {
            return data_;
        }

    private:
        
        std::string data_;

        int id_;

        std::string name_;
};
}
