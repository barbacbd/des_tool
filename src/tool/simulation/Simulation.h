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
    int findMinAvailableQueue();

    /**
     * @param vec - vector of Queues to search for the maximum in
     * @return - index of the QUEUE with the max current elements, -1 if there is a failure
     */
    int findMaxQueue();

    /**
     * @param vec - vector of Server to find the minimum in
     * @return - index of the Server with the minimum total, -1 if there is a failure.
     */
    int findMinAvailableServer();

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
     * Search through the servers and remove the event from the server
     * if it exists. NOTE: this should only find ONE event. It will only
     * remove the first one that it finds.
     * @param e - event to search for
     * @return True if found and removed event, otherwise false.
     */
    bool removeEvent(Event &e);

    /**
     * Go through all servers that have open room, and move
     * elements from the queues that are available
     */
    void queueToServer();

    /**
     * As we progress through the simulation keep track of what event has hit what stage.
     * @param e - event in m_tracked_events to change;
     * @param stage - stage that the event is set to.
     */
    void alterEventStage(Event e, EVENT_STAGE stage);

private:
    std::vector<Event> m_events;
    std::vector<DESQueue> m_queues;
    std::vector<DESServer> m_servers;
    std::map<EVENT_TYPE, int> m_event_types;

    std::vector<Event> m_tracked_events;

    std::vector<Record> m_records;
};


#endif //DESTOOL_SIMULATION_H
