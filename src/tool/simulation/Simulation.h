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
             std::vector<DESQueue> queues,
             std::vector<DESServer> servers,
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

    std::vector<Record> getRecords() { return m_records; }

protected:

    ///
    /// NOTE: these find functions should be able to be combined but we aren't using
    /// pointer so I cannot seem to pass the base class
    ///

    /**
     * @param vec - vector of QUEUE to find the minimum in
     * @return - index of the QUEUE with the minimum total, -1 if there is a failure.
     */
    int findMinAvailableQueue(std::vector<DESQueue> vec);

    /**
     * @param vec - vector of Queues to search for the maximum in
     * @return - index of the QUEUE with the max current elements, -1 if there is a failure
     */
    int findMaxQueue(std::vector<DESQueue> vec);

    /**
     * @param vec - vector of Server to find the minimum in
     * @return - index of the Server with the minimum total, -1 if there is a failure.
     */
    int findMinAvailableServer(std::vector<DESServer> vec);

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

    /**
     * Go through all servers that have open room, and move
     * elements from the queues that are available
     */
    void queueToServer();

private:
    std::vector<Event> m_events;
    std::vector<DESQueue> m_queues;
    std::vector<DESServer> m_servers;
    std::map<EVENT_TYPE, int> m_event_types;

    std::vector<Record> m_records;
};


#endif //DESTOOL_SIMULATION_H
