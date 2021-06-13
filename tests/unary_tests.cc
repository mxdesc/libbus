#include <algorithm>
#include <criterion/criterion.h>
#include <fstream>
#include <iostream>


#include "libbus/Bus.hh"
#include "libbus/ClientInterface.hh"
#include "libbus/Event.hh"

#include "Client.hh"

namespace libbus
{
    Test(unary_tests, send_from_registered_source)
    {
        Client A("A");

        Bus<Client> bus;

        bus.register_source("Source 1");

        try{
            bus.send(Event("message", 1, "Source 1"));
        }
        catch(const std::invalid_argument &e){
            cr_assert(0);
        }

        cr_assert(1);

    }

    Test(unary_tests, send_from_not_registered_source)
    {

        Client A("A");

        Bus<Client> bus;

        try{
            bus.send(Event("message", 1, "Not registered Source"));
        }
        catch(const std::invalid_argument &e){
            cr_assert(1);
            return;
        }

        cr_assert(0);
    }

    Test(unary_tests, send_from_unregistered_source)
    {
        
        
        Client A("A");

        Bus<Client> bus;

        bus.register_source("Source 1");

        bus.unregister_source("Source 1");

        try{
            bus.send(Event("message", 1, "Source 1"));
        }

        catch(const std::invalid_argument &e){
            cr_assert(1);
            return;
        }

        cr_assert(0);

    }

    Test(unary_tests, send_to_multiple_clients)
    {
        Client A("A");
        Client B("B");

        Bus<Client> bus;

        bus.register_source("Source 1");

        try{
            bus.send(Event("Message", 1, "Source 1"));
        }
        catch(const std::invalid_argument &e){
            cr_assert(0);
        }

        cr_assert(1);
    }
    
    Test(unary_tests, register_source)
    {
        Bus<Client> bus;

        std::vector<std::string> sources = {"Source 1", "Source 2", "Source 3"};

        for (auto source : sources)
            bus.register_source(source);

        for (auto source : sources)
        {
            if (!bus.is_registered(source))
            {
                cr_assert(0);
            }
        }

    }

    Test(unary_tests, register_same_source)
    {
        Bus<Client> bus;

        bus.register_source("Source 1");

        try{
             bus.register_source("Source 1");
        }

        catch(const std::invalid_argument &e){
            return;
        }
      
        cr_assert(0);
    }
    
    Test(unary_tests, unregister_source)
    {
        Client A("A");
        Client B("B");

        Bus<Client> bus;

        bus.register_source("Source 1");

        bus.subscribe(A, "Source 1");
        bus.subscribe(B, "Source 1");

        bus.unregister_source("Source 1");

        if (bus.is_registered("Source 1"))
            cr_assert(0);
    
        //check if subscriber source's list has been reset too :

        //register the source again        
        bus.register_source("Source 1");

        //verify that Client A and Client B are not subscribed anymore to Source 1
        if (bus.is_sub(A, "Source 1") || bus.is_sub(B, "Source 1"))
            cr_assert(0);
    }

    Test(unary_tests, unregister_not_registered_source)
    {

        Bus<Client> bus;

        try{
        bus.unregister_source("Unknown Source");
        }
        catch (const std::invalid_argument &e){
            return;
        }

        cr_assert(0);
    }


    Test(unary_tests, subscribe_and_unsubscribe)
    {
        Client A("A");

        Bus<Client> bus;

        bus.register_source("Source 1");

        bus.subscribe(A, "Source 1");

        bus.unsubscribe(A, "Source 1");

        if (bus.is_sub(A, "Source 1"))
            cr_assert(0);
    }

    Test(unary_tests, subscribe_unsubscribe_mutiple_sources_)
    {
        Client A("A");

        Bus<Client> bus;

        std::vector<std::string> sources = {"Source 1", "Source 2", "Source 3"};

        for (auto source : sources)
        {
            bus.register_source(source);
            bus.subscribe(A, source);
        }

        bus.unsubscribe(A, "Source 2");

        //check that Client A is still sub to Source 1 and 3
        if (!(bus.is_sub(A, "Source 1") && bus.is_sub(A, "Source 3")))
            cr_assert(0);

        //check that Client A is not sub to Source 2
        if (bus.is_sub(A, "Source 2"))
            cr_assert(0);
    }

}

