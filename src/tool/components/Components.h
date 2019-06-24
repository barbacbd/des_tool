/**
 * Author: Brent Barbachem
 * Date:   6/23/19.
 */

#ifndef DESTOOL_COMPONENTS_H
#define DESTOOL_COMPONENTS_H

#include <QString>

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

class Event
{
public:
    Event(QString id, EVENT_TYPE type, double time)
    {
        m_id=id;
        m_type=type;
        m_time=time;
    }

    std::string toString()
    {
        std::string event_str = "";
        switch(m_type)
        {
            case ARRIVAL: event_str = "ARRIVAL"; break;
            case DEPARTURE: event_str = "DEPARTURE"; break;
            case TERMINATE: event_str = "TERMINATE"; break;
        }

        return m_id.toStdString() + " (" + event_str + ") occurred at " + std::to_string(m_time);
    }

    QString getID() const { return m_id; }
    EVENT_TYPE getType() const { return m_type; }
    double getTime() const { return m_time; }

    void setID(QString id) { m_id = id; }
    void setType(EVENT_TYPE type) { m_type = type; }
    void setTime(double time) { m_time = time; }

protected:
    QString m_id;
    EVENT_TYPE m_type;
    double m_time;
};


class Container
{
public:
    Container(QString id, int capacity, std::vector<Event> events)
    {
        m_id = id;
        m_capacity = capacity;
        m_events = events;
    }

    std::string toString()
    {
        return "";
    }

    /// public getter fucntions, no setters (this class is essentially immutable)
    QString getID() { return m_id; }
    int getCapacity() { return m_capacity; }
    std::vector<Event> getEvents() { return m_events; }

    virtual bool addEvent(Event &e)
    {
        if(m_events.size() < m_capacity)
        {
            m_events.emplace_back(e);
            return true;
        }

        return false;
    }

protected:
    QString m_id;
    int m_capacity;
    std::vector<Event> m_events;
};

class DESQueue : public Container
{
public:
    DESQueue(QString id, int capacity, std::vector<Event> events, QUEUE_TYPE type)
    : Container(id, capacity, events)
    {
        m_type = type;
    }


    std::string toString()
    {
        return "";
    }

    /// public getter not setters
    QUEUE_TYPE getType() { return m_type; }

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
        }
    }

protected:
    QUEUE_TYPE m_type;
};


//struct Record {
//    double time;
//    std::vector<Event> events;
//    std::vector<Container> servers;
//    std::vector<Queue> queues;
//};
//


#endif //DESTOOL_COMPONENTS_H
