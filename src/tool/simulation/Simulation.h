/**
 * Author: Brent Barbachem
 * Date:   6/28/19.
 */

#include "../components/Components.h"
#include <map>

#ifndef DESTOOL_SIMULATION_H
#define DESTOOL_SIMULATION_H


class Simulation
{
public:
    /**
     * @param events - list of ORDERED events
     * @param queues - list of queues
     * @param servers - list of servers
     * @param event_types - map that tells the order of events and their priority
     */
    Simulation(std::vector<Event> events,
             std::vector<Container*> queues,
             std::vector<Container*> servers,
             std::map<EVENT_TYPE , int> event_types);

    /**
     * Delete any dynamically allocated memory
     */
    ~Simulation();

    /**
     * Run through the simulation creating a record for each time
     * step. As the user progresses through the graphical interface, they
     * will see each record on the screen.
     */
    void run();

protected:
    /**
     * Function to find the minimum container from the list provided. We should be able to
     * pass both of our lists for queues and servers since they are both technically containers.
     * @param vec - vector of containers to find the minimum in
     * @return - index of the container with the minimum capacity, -1 if there is a failure.
     */
    int findMinAvailableContainer(std::vector<Container*> vec);

    /**
     * Find the index of the termination event.
     * @return position of the termination event. -1 if failed to find one.
     */
    int findTermination();

    /**
     *
     * @param cpos
     * @return
     */
    std::map<EVENT_TYPE, Event> getNextEventList(int cpos);

    /**
     *
     * @param e
     * @return
     */
    bool removeEvent(Event &e);

private:
    std::vector<Event> m_events;
    std::vector<Container*> m_queues;
    std::vector<Container*> m_servers;
    std::map<EVENT_TYPE, int> m_event_types;
};


#endif //DESTOOL_SIMULATION_H
