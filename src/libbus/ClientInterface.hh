#include "Event.hh"

#include <iostream>

#pragma once

namespace libbus{

class ClientInterface{

    public:

    virtual void receive(Event event)
    {
        std::cout << "ClientInterface receive " << event.get_data() << "!" << std::endl;
    }

    virtual ~ClientInterface() = default;

};
}
