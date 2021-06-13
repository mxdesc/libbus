#include "Event.hh"
#include "ClientInterface.hh"

#include <vector>
#include <map>

#include <functional>

#include <iostream>
#include <memory>

#include <set>

#pragma once

namespace libbus{
template <typename ClientInterface>
class Bus{

    public:

        void send(Event event)
        {
            auto const sourcename = event.get_name();

            if (trusted_sources_.find(sourcename) == trusted_sources_.end())
                throw std::invalid_argument("The source \"" + sourcename + "\" is not registered: Entity cannot be sended");

            for (auto const &sub : infos_[sourcename])
                sub.get().receive(event);
        }

        
        template <typename DerivedClient>
        void subscribe(DerivedClient& client, std::string sourcename)
        {
            //check if the source name is valid, throw an exception if not
            if (!is_registered(sourcename))
                throw std::invalid_argument("Cannot subscribe a client to source \"" + sourcename + "\" because it is not registered.");

            
            //check if the client is already subscribed to the source
            if (is_sub(client, sourcename))
                throw std::invalid_argument("This client is already subscribed to the source " + sourcename + ".");

            //else, the client is added to the corresponding vector of the map
            infos_[sourcename].push_back(std::reference_wrapper<DerivedClient>(client));
        }

        template <typename DerivedClient>
        void unsubscribe(DerivedClient& client, std::string sourcename)
        {    
            size_t i = 0;

            for (auto const &elt : infos_[sourcename])
            {
                if (&elt.get() == &client)
                    break;

                i++;
            }

            infos_[sourcename].erase(infos_[sourcename].begin() + i);
        }


        void register_source(std::string sourcename)
        {
            if (trusted_sources_.find(sourcename) != trusted_sources_.end())
                throw std::invalid_argument("The source \"" + sourcename 
                    + "\" is already registerd!");
            else
            {
                trusted_sources_.insert(sourcename);
                
                //this line is to instanciate an empty vector 
                //(useful for the pretty print) 
                infos_[sourcename];
            }
        }
        
        //unregister a source and unsubscribe every client 
        //subscribed to this source 
        //if alert is true, an alert is sent to every client concerned
        void unregister_source(std::string sourcename, bool alert = false)
        {
            if (trusted_sources_.find(sourcename) == trusted_sources_.end())
                throw std::invalid_argument("The source \"" + sourcename
                    + "\" is not registerd!");
            else
            {
                if (alert)
                    send(Event(sourcename + " is not a registered source anymore, you have been unsubscribed from it. ", 0, sourcename));

                for (auto const &client : infos_[sourcename])
                    unsubscribe( client.get() ,sourcename);
                
                trusted_sources_.erase(sourcename);
            }
        }

        //check if the given client is subscribed to the sourcename
        template <typename DerivedClient>
        bool is_sub(DerivedClient &client, std::string sourcename)
        {
            auto subs = infos_[sourcename];

            for (auto sub : subs)
            {
                if (&sub.get() == &client)
                    return true;
            }

            return false;
        }

        //print some informations about the actual state of the bus
        void pretty_print()
        {
            std::cout << "The bus trust the following sources :" << std::endl;

            for (auto const &sourcename : trusted_sources_)
                std::cout << "- " << sourcename << std::endl;

            std::cout << "Bus informations says that :" << std::endl;

            for (auto const &pair : infos_)
            {
                std::cout << "- " << pair.first << " got "
                    << pair.second.size() << " subscribers." << std::endl;
            }
        }

        bool is_registered(std::string sourcename)
        {
             if (trusted_sources_.find(sourcename) != trusted_sources_.end())
                 return true;

             return false;
        }


    private:

        std::set<std::string> trusted_sources_;

        std::map<std::string, std::vector<std::reference_wrapper<ClientInterface>>> infos_;

};
}
