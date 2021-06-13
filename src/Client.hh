#include "libbus/ClientInterface.hh"
#include "libbus/Event.hh"

#include <iostream>

#pragma once 

using namespace libbus;

class Client : public ClientInterface{

    public :
        Client(std::string name)
        {
            this->name_ = name;
        }

    void receive(Event event) override final{

        std::cout << "I am Client "<< name_ <<" and i received something from "<< event.get_name() << ": " << event.get_data() << std::endl;

    }

    std::string get_name()
    {
        return this->name_;
    }

    private :
        std::string name_;
};

