/**
 * Author: Brent Barbachem
 * Date:   6/23/19.
 */

#ifndef DESTOOL_COMPONENTS_H
#define DESTOOL_COMPONENTS_H

#include <QString>
#include <iostream>
#include <sstream>

enum EVENT_TYPE
{
    ARRIVAL,
    DEPARTURE,
    TERMINATE
};

enum QUEUE_TYPE
{
    FIFO,
    LIFO
};

enum EVENT_STAGE
{
    NO_EXIT,    /// NEVER left the system
    EARLY_EXIT, /// Departure event caused removal from queue (never processed)
    CLEAN_EXIT, /// EXITED properly on departure (from server)
    PROCESSED   /// Moved to Server
};

class Event
{
public:

    /**
     * OVERRIDE Constructor
     */
    Event() {}

    /**
     * Normal constructor for the EVENT
     * @param id - identifier for the Event
     * @param type - EVENT_TYPE
     * @param time - time that the event occurred
     */
    Event(std::string id, EVENT_TYPE type, double time) : m_id(id), m_type(type), m_time(time), m_stage(NO_EXIT) {}

    /**
     * COPY CONSTRUCTOR - shallow copy
     * @param e - EVENT Object that the information is copied from
     */
    Event(const Event &e)
    {
        m_id = e.m_id;
        m_type = e.m_type;
        m_time = e.m_time;
        m_stage = e.m_stage;
    }

    /**
     * JAVA Style to string function so that the object can be printed out. We could have
     * created a friend function and passed in the iostream. Decided that this particular
     * design was how I wanted to implement this functionality.
     * @return String representation of the EVENT
     */
    std::string toString()
    {
        std::string event_str = "";
        switch(m_type)
        {
            case ARRIVAL: event_str = "ARRIVAL"; break;
            case DEPARTURE: event_str = "DEPARTURE"; break;
            case TERMINATE: event_str = "TERMINATE"; break;
        }

        return m_id + " (" + event_str + ") occurred at " + std::to_string(m_time);
    }

    /// getter functions for the Event
    std::string getID() const { return m_id; }
    EVENT_TYPE getType() const { return m_type; }
    double getTime() const { return m_time; }
    EVENT_STAGE  getStage() const {return m_stage;}

    /// setter functions for the Event
    void setID(std::string id) { m_id = id; }
    void setType(EVENT_TYPE type) { m_type = type; }
    void setTime(double time) { m_time = time; }
    void setStage(EVENT_STAGE stage) { m_stage = stage; }

protected:
    std::string m_id;
    EVENT_TYPE m_type;
    double m_time;
    EVENT_STAGE m_stage;
};


class Container
{
public:
    /**
     * OVERRIDE CONSTRUCTOR
     */
    Container() {}

    /**
     * Normal constructor for the Container object
     * @param id - identifier for the container
     * @param capacity - max number of events in the container
     * @param events - list of events currently in the container
     */
    Container(std::string id, int capacity, std::vector<Event> events)
    : m_id(id), m_capacity(capacity), m_events(events) {}

    /**
     * COPY CONSTRUCTOR - shallow copy
     * @param c - Container object to copy information from
     */
    Container(const Container &c) : m_id(c.m_id), m_capacity(c.m_capacity), m_events(c.m_events) {}

    /**
     * JAVA Style to string function so that the object can be printed out. We could have
     * created a friend function and passed in the iostream. Decided that this particular
     * design was how I wanted to implement this functionality.
     * @return String representation of the Container
     */
    virtual std::string toString() = 0;


    /// public getter fucntions, no setters (this class is essentially immutable)
    std::string getID() { return m_id; }
    int getCapacity() { return m_capacity; }
    std::vector<Event> getEvents() { return m_events; }

    /**
     * Add an event to the container. In a normal container the events are added to the back
     * of the list. This function is virtual and the children can choose to override it.
     * @param e - Event that we wish to add to the back of the list
     * @return - True if the event was successfully added
     */
    virtual bool addEvent(Event &e)
    {
        if(m_events.size() < m_capacity)
        {
            m_events.emplace_back(e);
            return true;
        }

        return false;
    }

    /**
     * Remove the event from the list of events. This is not a dequeue function; we will only
     * remove the item (no matter where it is).
     * @param e - Event containing the id that we wish to remove
     * @return True if successful removal
     */
    virtual bool removeEvent(Event &e)
    {
        std::vector<Event>::iterator it = std::remove_if(m_events.begin(), m_events.end(),
                [e] (const Event& event) { return event.getID() == e.getID(); } );

        if(it != m_events.end())
        {
            m_events.erase(it);
            return true;
        }

        return false;
    }

protected:
    std::string m_id;
    int m_capacity;
    std::vector<Event> m_events;
};

class DESServer : public Container
{
public:
    /**
     * OVERRIDE Constructor
     */
    DESServer() : Container() {}

    /**
     * Normal constructor for the DES Server
     * @param id - Name of the server
     * @param capacity - capacity of the server
     * @param events - list of events currently in the queue
     */
    DESServer(std::string id, int capacity, std::vector<Event> events)
    : Container(id, capacity, events) {}

    /**
     * COPY CONSTRUCTOR - shallow copy
     * @param q - DESServer object to copy information from
     */
    DESServer(const DESServer &q) : Container(q.m_id, q.m_capacity, q.m_events) {}

    /**
     * JAVA Style to string function so that the object can be printed out. We could have
     * created a friend function and passed in the iostream. Decided that this particular
     * design was how I wanted to implement this functionality.
     * @return String representation of the DESServer
     */
    virtual std::string toString()
    {
        std::stringstream ss;
        ss << "DESServer: " << m_id << " Capacity: " << m_capacity << " Total: " << m_events.size() << std::endl;

        for(auto &e : m_events)
        {
            ss << e.toString() << std::endl;
        }

        return ss.str();
    }

};

class DESQueue : public Container
{
public:
    /**
     * OVERRIDE Constructor
     */
    DESQueue() : Container() {}

    /**
     * Normal constructor for the DES Queue
     * @param id - Name of the queue
     * @param capacity - capacity of the queue
     * @param events - list of events currently in the queue
     * @param type - Queue type FIFO or LIFO
     */
    DESQueue(std::string id, int capacity, std::vector<Event> events, QUEUE_TYPE type)
    : Container(id, capacity, events), m_type(type) {}

    /**
     * COPY CONSTRUCTOR - shallow copy
     * @param q - DESQueue object to copy information from
     */
    DESQueue(const DESQueue &q) : Container(q.m_id, q.m_capacity, q.m_events), m_type(q.m_type) {}

    /**
     * JAVA Style to string function so that the object can be printed out. We could have
     * created a friend function and passed in the iostream. Decided that this particular
     * design was how I wanted to implement this functionality.
     * @return String representation of the DESQueue
     */
    virtual std::string toString()
    {
        std::stringstream ss;
        ss << "DESQueue: " << m_id << " " << int(m_type) << " Capacity: " << m_capacity << " Total: "
        << m_events.size() << std::endl;

        for(auto &e : m_events)
        {
            ss << e.toString() << std::endl;
        }

        return ss.str();
    }

    /// public getter not setters
    QUEUE_TYPE getType() { return m_type; }

    /**
     * Add the event to the list of events. If this is a FIFO queue then it is added to the back, otherwise
     * the event is added to the front of the list.
     * @param e - Event that we wish to add to the Container
     * @return - True if the Event was successfully added to the list of events
     */
    bool addEvent(Event &e)
    {
        if(m_events.size() < m_capacity)
        {
            if (m_type == FIFO)
            {
                m_events.emplace_back(e);
            }
            else
            {
                m_events.emplace(m_events.begin(), e);
            }
            return true;
        }

        return false;
    }

    /**
     * @return a shallow copy of the next event to be removed.
     */
    Event getNextExit()
    {
        if(m_events.size() <= 0)
        {
            return Event();
        }
        else
        {
            return m_events[0];
        }
    }

    /**
     * Remove the first Event from the list of events. If this is a fifo queue remove the first element
     * otherwise remove the last element of the list (LIFO).
     * @return True if successful
     */
    bool dequeue()
    {
        if(m_events.size() <= 0)
        {
            return false;
        }

        /// the addEvent function adds the data to the correct end of the
        /// list, so we can just remove the first element from now on.
        m_events.erase(m_events.begin());

        return true;
    }

protected:
    QUEUE_TYPE m_type;
};

class Record
{
public:
    /**
     * OVERRIDE Constructor
     */
    Record() {}

    /**
     * Copy Constructor
     * @param r - Record to initialize this record with
     */
    Record(const Record &r)
    {
        m_time = r.m_time;
        m_queues = r.m_queues;
        m_servers = r.m_servers;
    }

    /// public getter and setter functions
    void setTime(double time) { m_time = time; }
    void setServers(std::vector<DESServer> servers) { m_servers = servers; }
    void setQueues(std::vector<DESQueue> queues) { m_queues = queues; }

    double getTime() {return m_time; }
    std::vector<DESServer> getServers() { return m_servers; }
    std::vector<DESQueue> getQueues() { return m_queues; }

    /**
     * JAVA Style to string function so that the object can be printed out. We could have
     * created a friend function and passed in the iostream. Decided that this particular
     * design was how I wanted to implement this functionality.
     * @return String representation of the Record
     */
    std::string toString()
    {
        std::stringstream ss;
        ss << "RECORD: " << m_time << std::endl;

        for(auto &q : m_queues)
        {
            ss << q.toString() << std::endl;
        }

        for(auto &s : m_servers)
        {
            ss << s.toString() << std::endl;
        }

        return ss.str();
    }

private:
    double m_time;
    std::vector<DESQueue> m_queues;
    std::vector<DESServer> m_servers;
};


#endif //DESTOOL_COMPONENTS_H
