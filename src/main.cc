#include "libbus/Bus.hh"
#include "libbus/Event.hh"
#include "libbus/ClientInterface.hh"
#include <iostream>

//for tests:
#include "Client.hh"

using namespace libbus;

int main(void)
{

    Client A("A");
    Client B("B");
    Client C("C");

    Bus<Client> bus;

    std::cout << "Registering Source 1...";
    bus.register_source("Source 1");
    std::cout << "Done !" << std::endl;
    
    std::cout << "Subscribing Client A and Client B to Source 1...";
    bus.subscribe<Client>(A, "Source 1");
    bus.subscribe<Client>(B, "Source 1");
    std::cout << "Done !" << std::endl;

    if(bus.is_sub(A, "Source 1"))
    {
        std::cout << "Client " + A.get_name() + " is subscribed to Source 1." << std::endl;
    }

    if(bus.is_sub(B, "Source 1"))
    {
        std::cout << "Client " + B.get_name() + " is subscribed to Source 1." << std::endl;
    }

    Event event("Only A and B should receive this.", 1, "Source 1");

    std::cout << "\nSending an event from Source 1...\n";
    bus.send(event);
    std::cout << "Sent !\n" << std::endl;


    std::cout << "Trying to send entity from an unknown source :\n";
    try{
        //send from an unregistered source that should fail
        bus.send(Event("A message", 2, "Unknown Source"));
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << "exception: " << e.what() << std::endl;

    }

    std::cout << "Trying to subscribe a client to an unknown source :\n";
    try{
        bus.subscribe(A, "Unknown Source");
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << "exception: " << e.what() << std::endl;

    }

    std::cout << "\nRegistering Source 2 and Source 3...";
    bus.register_source("Source 2");
    bus.register_source("Source 3");
    std::cout << "Done !\n" << std::endl;

    std::cout << "Trying to register the same source several times :\n";
    try{
        //should fail because Source 2 is already registered
        bus.register_source("Source 2");
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << "exception: " << e.what() << std::endl;
    }

    std::cout << "\nSubscribing Client A and Client C to Source 2...";
    bus.subscribe(C, "Source 2");
    bus.subscribe(A, "Source 2");
    std::cout << "Done !\n" << std::endl;
    
    std::cout << "Trying to subscribe a client to a source several times :\n";
    try{
        //should fail because Client C is already subscribed to Source 2
        bus.subscribe(C, "Source 2");
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << "exception: " << e.what() << std::endl;
    }

    /*
    std::cout << "\nBus pretty printing :\n";
    bus.pretty_print();
    */

    std::cout << "\nSending an event from Source 2...\n";
    bus.send(Event("A and C receive this", 2, "Source 2"));
    std::cout << "Sent !" << std::endl; 

    std::cout << "\nUnsubscribing B from Source 1...";
    bus.unsubscribe(B, "Source 1");
    std::cout << "Done !" << std::endl;

    if(!bus.is_sub(B, "Source 1"))
    {
        std::cout << "Client " + B.get_name() + " is not sub to Source 1 !" << std::endl;
    }

    bus.send(Event("Only A will receive this !", 3, "Source 1"));

    std::cout << "\nUnregistering Source 1...";
    bus.unregister_source("Source 1");
    std::cout << "Done !" << std::endl;
    
    //try to send from an unregistered source will throw an exception
    try{
        bus.send(event);
    }
    catch(const std::invalid_argument& e){
        std::cerr << "exception: " << e.what() << std::endl;
    }

    //try to subscribe to an unregistered source will throw an exception
    try{
        bus.subscribe<Client>(A, "Source 1");

    }
    catch(const std::invalid_argument& e){
        std::cerr << "exception: " << e.what() << std::endl;
    }

    std::cout << "\nRegistering Source 1 again...";
    bus.register_source("Source 1");
    std::cout << "Done !" << std::endl;

    std::cout << "Sending an event from Source 1...";
    //nobody should receive it because the source is Source 1, that has
    //been unregistered and then registered (its subscribers have been reset)
    bus.send(event);
    std::cout << "Sent !" << std::endl;
    

    std::cout << "\nUnregistering Source 2 and alerting its subscribers...\n";
    //alert parameter is set to true when calling the unregister_source() function
    bus.unregister_source("Source 2", true);
    std::cout << "Done !" << std::endl;
    
    //bus.pretty_print();

    return 0;
}
