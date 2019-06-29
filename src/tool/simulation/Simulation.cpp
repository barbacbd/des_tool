/**
 * Author: Brent Barbachem
 * Date:   6/28/19.
 */

#include "Simulation.h"
#include <iostream>


Simulation::Simulation(std::vector<Event> events,
        std::vector<Container*> queues,
        std::vector<Container*> servers,
        std::map<EVENT_TYPE , int> event_types)
        : m_events(events), m_queues(queues), m_servers(servers), m_event_types(event_types)
{

}

Simulation::~Simulation()
{

}

void Simulation::run()
{
        if(m_servers.empty() || m_events.empty() || m_queues.empty())
        {
                /// don't try to simulate if there is missing information
                return;
        }

//        m_records.clear();

        /// create Records that can be used as a step in time that will
        /// show queue and server state information
        for( auto& event : m_events)
        {

                bool end_simulation = false;

                switch(event.getType())
                {
                        case ARRIVAL:
                        {
                                std::cout << event.toString() << std::endl;

                                int min_avail_server = findMinAvailableContainer(m_servers);
                                if(min_avail_server >= 0)
                                {
                                        /// send the event straight to the server
                                        m_servers[min_avail_server]->addEvent(event);
                                }
                                else
                                {
                                        /// find the minimum queue
                                        int min_avail_queue = findMinAvailableContainer(m_queues);
                                        if(min_avail_queue >= 0)
                                        {
                                                m_queues[min_avail_queue]->addEvent(event);
                                        } else { continue; }
                                }


                        }
                        break;

                        case DEPARTURE:
                        {
                                std::cout << event.toString() << std::endl;

                                if(!removeEvent(event))
                                {
//                                    queueToServer();
                                }
                        }
                        break;

                        case TERMINATE:
                        {
                                std::cout << event.toString() << std::endl;
                                end_simulation = true;
                        }
                        break;
                }

//                /// create the record that can be saved as a snapshot
//                Record r;
//                r.time = e.time;
//
//                /// these calls should hit the copy constructor of each
//                /// of the classes and then a shallow copy should be made
//                for(auto &queue : m_queues)
//                {
//                        r.queues.push_back(queue);
//                }
//
//                for(auto &server : m_servers)
//                {
//                        r.servers.push_back(server);
//                }
//
//                /// add the record to our list
//                m_records.push_back(r);

                /// time to end the creation of records ... which means the end of simulation !
                if(end_simulation)
                {
                        break;
                }

        }

        std::cout << "Finished" << std::endl;
}

int Simulation::findMinAvailableContainer(std::vector<Container*> vec)
{
        int min_size = std::numeric_limits<int>::max();

        int pos = 0;
        int min_pos = -1;
        for(auto &container : vec)
        {
                uint64_t size = container->getEvents().size();

                if(size < min_size && size < container->getCapacity())
                {
                        min_pos = pos;
                }
                pos ++;
        }

        return min_pos;
}

int Simulation::findTermination()
{
        int pos = 0;
        for(auto &e : m_events)
        {
                if(e.getType() == TERMINATE)
                {
                        return pos;
                }
                pos ++;
        }

        return -1;
}

std::map<EVENT_TYPE, Event> Simulation::getNextEventList(int cpos)
{
        bool arrival = false;
        bool departure = false;
        bool termination = false;

        std::map<EVENT_TYPE, Event> next_events;

        int pos = 0;
        for(const Event &event : m_events)
        {

            switch(event.getType())
            {
                case ARRIVAL:
                {
                    if(!arrival)
                    {
                        next_events[ARRIVAL] = Event(event);
                        arrival = true;
                    }
                } break;

                case DEPARTURE:
                {
                    if(!departure)
                    {
                        next_events[DEPARTURE] = Event(event);
                        departure = true;
                    }
                } break;

                case TERMINATE:
                {
                    if(!termination)
                    {
                        next_events[TERMINATE] = Event(event);
                        termination = true;
                    }
                } break;
            }

            pos ++;
        }

        return next_events;
}


bool Simulation::removeEvent(Event &e)
{
        for(auto &server : m_servers)
        {
                if(server->removeEvent(e))
                {
                        return true;
                }
        }

        return false;
}