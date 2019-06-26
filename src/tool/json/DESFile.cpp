#include "DESFile.h"
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <functional>
#include <QVariant>
#include <limits>

DESFile::DESFile(QString filename)
{
    /// NOTE: if filename is empty is becomes pretty much useless, the use will
    /// have to create a new file and read from it.

    if(!filename.isEmpty())
    {
        m_filename = filename;

        /// select the filetype for later so it is now an easier comparison than text
        if(m_filename.endsWith(".txt"))
        {
            m_file_type = TXT;
        }
        else if(m_filename.endsWith(".json"))
        {
            m_file_type = JSON;
        }
        else
        {
            m_file_type = UNSUPPORTED;
        }

        read();
    }
}

DESFile::~DESFile()
{
    for(auto &i : m_queues)
    {
        delete i;
    }

    for(auto &i : m_servers)
    {
        delete i;
    }
}

void DESFile::read()
{
    /// NOTE: filename cannot be empty here, so we are not going to check

    /// Create, open, and read the file information to a variable
    QFile file(m_filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString data=file.readAll();
    file.close();


    switch(m_file_type)
    {
        case TXT: parseTXT(data); break;
        case JSON: parseJSON(data); break;

        /// add any new file type here

        case UNSUPPORTED:
        default:
            /// do nothing, but adding a return in case code is added below or outside of the switch
            return;
    }
}

void DESFile::parseTXT(QString data)
{

}

void DESFile::parseJSON(QString data)
{
    /// convert the string to a json document and get the first object {}
    m_doc = QJsonDocument::fromJson(data.toUtf8());

    QJsonValue events = getJsonValue("EVENTS");
    QJsonValue order = getJsonValue("EVENT_ORDER");
    if(events.isArray() && order.isArray())
    {
        orderEvents(events, order);
    }

    QJsonValue servers = getJsonValue("SERVERS");
    if(servers.isArray())
    {
        createServers(servers);
    }

    QJsonValue queues = getJsonValue("QUEUES");
    if(queues.isArray())
    {
        createQueues(queues);
    }

    /// run the simualation now that all information has been read in.
    simulate();
}

/**
 * TODO: make the search a string that is not case sensitive
 */
QJsonValue DESFile::getJsonValue(QString name)
{
    QJsonValue json_value;
    if(m_doc.isObject())
    {
        QJsonObject json = m_doc.object();
        if(!json[name].isNull())
        {
            json_value = json[name];
        }
    }

    return json_value;
}

/// function to create events
void DESFile::orderEvents(QJsonValue events, QJsonValue order)
{
    QJsonArray event_array = events.toArray();
    QJsonArray order_array = order.toArray();

    int pos = 0;
    for(QJsonArray::iterator it = order_array.begin(); it != order_array.end(); it++, pos++)
    {
        QString type = (*it).toString();

        /// set the priority for each type of EVENT
        /// BUT ... DO NOT set the value more than once
        /// i.e Arrival, D, TERMINATE , ARRIVAL would yield [A, D, T]
        if(type.startsWith('A', Qt::CaseInsensitive) && m_event_types.find(ARRIVAL) == m_event_types.end())
        {
            m_event_types[ARRIVAL] = pos;
        }
        else if(type.startsWith('D', Qt::CaseInsensitive) && m_event_types.find(DEPARTURE) == m_event_types.end())
        {
            m_event_types[DEPARTURE] = pos;
        }
        else if(type.startsWith('T', Qt::CaseInsensitive) && m_event_types.find(TERMINATE) == m_event_types.end())
        {
            m_event_types[TERMINATE] = pos;
        }

        /// New Event Types can be added here, but generally DES is only worried about A,D,T

    }

    /// create the list of all events
    foreach (const QJsonValue & value, event_array)
    {
        QJsonObject obj = value.toObject();

        /// get the entity number [if exists], event type, and time
        QString entity = "";
        double time;
        EVENT_TYPE type;

        QJsonValue entityValue = obj["ENTITY"];
        if(!entityValue.isNull())
        {
            entity=entityValue.toVariant().toString();
        }

        QJsonValue timeValue = obj["TIME"];
        if(timeValue.isDouble())
        {
            time = timeValue.toDouble();
        }
        else
        {
            continue;
        }

        QJsonValue typeValue = obj["TYPE"];
        if(typeValue.isString())
        {
            if(typeValue.toString().startsWith('A', Qt::CaseInsensitive))
            {
                type = ARRIVAL;
            }
            else if(typeValue.toString().startsWith('D', Qt::CaseInsensitive))
            {
                type = DEPARTURE;
            }
            else if(typeValue.toString().startsWith('T', Qt::CaseInsensitive))
            {
                type = TERMINATE;
            }
            else
            {
                continue;
            }
        }
        else
        {
            continue;
        }

        m_events.push_back(Event(entity, type, time));
    }

    /// sort the events based on time and type
    std::sort(m_events.begin(), m_events.end(),
            std::bind(&DESFile::compareEvents, this, std::placeholders::_1, std::placeholders::_2));
}

void DESFile::createServers(QJsonValue servers)
{
    QJsonArray server_array = servers.toArray();

    foreach (const QJsonValue &value, server_array)
    {
        QJsonObject obj = value.toObject();

        QString id;
        int capacity = 0;

        QJsonValue idValue = obj["ID"];
        if(!idValue.isNull())
        {
            id = idValue.toVariant().toString();
        }

        /// There is a toInt(), but let's be safe anc convert to a variant then try the int conversion
        QJsonValue capValue = obj["CAPACITY"];
        if(!capValue.isNull())
        {
            capacity = capValue.toVariant().toInt();
        }

        /// check to make sure the server id does not exist ???
        std::vector<Event> events;
        m_servers.emplace_back(new Container(id, capacity, events));
    }
}

void DESFile::createQueues(QJsonValue queues)
{
    QJsonArray queue_array = queues.toArray();

    foreach (const QJsonValue &value, queue_array)
    {
        QJsonObject obj = value.toObject();

        QString id;
        int capacity = 0;
        QUEUE_TYPE type;

        QJsonValue idValue = obj["ID"];
        if(!idValue.isNull())
        {
            id = idValue.toVariant().toString();
        }
        else
        {
            continue;
        }

        /// There is a toInt(), but let's be safe anc convert to a variant then try the int conversion
        QJsonValue capValue = obj["CAPACITY"];
        if(!capValue.isNull())
        {
            capacity = capValue.toVariant().toInt();
        }

        QJsonValue typeValue = obj["TYPE"];
        if(typeValue.isString()) {
            QString str = typeValue.toString();

            if(str.compare("FIFO", Qt::CaseInsensitive))
            {
                type = FIFO;
            }
            else
            {
                type = LIFO;
            }
        }
        else
        {
            continue;
        }

        std::vector<Event> events;

        /// check to make sure the server id does not exist ???
        m_queues.emplace_back(new DESQueue(id, capacity, events, type));
    }
}

bool DESFile::compareEvents(const Event &a, const Event &b)
{
    double a_time = a.getTime();
    double b_time = b.getTime();

    if(a_time < b_time)
    {
        return true;
    }
    else if(a_time == b_time)
    {
        return m_event_types[a.getType()] <= m_event_types[b.getType()];
    }
    else
    {
        return false;
    }
}


int DESFile::findMinAvailableContainer(std::vector<Container*> vec)
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

void DESFile::simulate()
{
    if(m_servers.empty() || m_events.empty() || m_queues.empty())
    {
        /// don't try to simulate if there is missing information
        return;
    }

    /// create Records that can be used as a step in time that will
    /// show queue and server state information
    for( auto& event : m_events)
    {

        bool end_simulation = false;

        switch(event.getType())
        {
            case ARRIVAL:
            {
//                std::cout << event.toString() << std::endl;

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
                    }
                    else
                    {
                        /// discard the item ... but let's log it or at least print it out.
                        std::cout << "EVENT Failed: " << event.toString() << std::endl;
                    }
                }


            }
            break;

            case DEPARTURE:
            {
                std::cout << event.toString() << std::endl;

//                if(removeEvent(m_servers, event.getID()))
//                {
//                    /// Add the next event to the minimum server
//                }
//                else
//                {
//                    /// if the event is still in the queue it will be removed and logged that it wasn't able
//                    /// to be processed ...
//                }

                /// search for the event in the queues, if exists, then remove it
                /// and add the event to a server
            }
            break;

            case TERMINATE:
            {
                std::cout << event.toString() << std::endl;
                end_simulation = true;
            }
            break;
        }


        /// time to end the creation of records ... which means the end of simulation !
        if(end_simulation)
        {
            break;
        }

    }

    std::cout << "Finished" << std::endl;

}