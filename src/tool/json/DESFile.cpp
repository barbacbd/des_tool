#include "DESFile.h"
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <functional>
#include <QVariant>

DESFile::DESFile(QString filename)
{
    setFilename(filename);
}

DESFile::~DESFile()
{
    /// remove anything created in this class
}

void DESFile::setFilename(QString filename)
{
    if(!filename.isEmpty())
    {
        m_filename = filename;
    }
}

void DESFile::read()
{
    if(m_filename.isEmpty())
    {
        return;
    }

    /// Create, open, and read the file information to a variable
    QFile file(m_filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString data=file.readAll();
    file.close();


    if(m_filename.endsWith(".txt"))
    {
        parseTXT(data);
    }
    else if(m_filename.endsWith(".json"))
    {
        parseJSON(data);
    }
}

void DESFile::parseTXT(QString data)
{

}

void DESFile::parseJSON(QString data)
{

    std::cout << "MADE IT HERE " << std::endl;

    /// convert the string to a json document and get the first object {}
    m_doc = QJsonDocument::fromJson(data.toUtf8());

    std::cout << data.toStdString() << std::endl;

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


    if(m_servers.empty() || m_events.empty() || m_queues.empty())
    {
        /// don't try to simulate if there is missing information
        return;
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
        std::string type = (*it).toString().toStdString();

        /// set the priority for each type of EVENT
        if(boost::iequals(type, "ARRIVAL") || boost::iequals(type, "A"))
        {
            m_event_types['A'] = pos;
        }
        else if(boost::iequals(type, "DEPARTURE") || boost::iequals(type, "D"))
        {
            m_event_types['D'] = pos;
        }
        else if(boost::iequals(type, "TERMINATE") || boost::iequals(type, "T"))
        {
            m_event_types['T'] = pos;
        }
    }

    /// create the list of all events
    foreach (const QJsonValue & value, event_array)
    {
        QJsonObject obj = value.toObject();

        /// get the entity number [if exists], event type, and time
        QString entity = "";
        double time;
        QChar type;

        QJsonValue entityValue = obj["ENTITY"];
        if(!entityValue.isNull())
        {
            entity = entityValue.toVariant().toString();
        }

        QJsonValue timeValue = obj["TIME"];
        if(timeValue.isDouble())
        {
            time = timeValue.toDouble();
        }

        QJsonValue typeValue = obj["TYPE"];
        if(typeValue.isString())
        {
            type = typeValue.toString().at(0);
        }

        m_events.push_back({entity, type, time});
    }

    /// sort the events based on time and type
    std::sort(m_events.begin(), m_events.end(), std::bind(&DESFile::compareEvents, this, std::placeholders::_1, std::placeholders::_2));
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
        m_servers.push_back({id, capacity, events});
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
        int type;

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

        QJsonValue typeValue = obj["TYPE"];
        if(typeValue.isString())
        {
            QString str = typeValue.toString();

            if(boost::iequals(str.toStdString(), "FIFO"))
            {
                type = FIFO;
            }
            else
            {
                type = LIFO;
            }
        }

        std::vector<Event> events;
        Container c = {id, capacity, events};

        /// check to make sure the server id does not exist ???
        m_queues.push_back({c, type});
    }
}

bool DESFile::compareEvents(const Event &a, const Event &b)
{
    if(a.time < b.time)
    {
        return true;
    }
    else if(a.time == b.time)
    {
        int type_a = m_event_types[a.type];
        int type_b = m_event_types[b.type];

        return type_a <= type_b;
    }
    else
    {
        return false;
    }
}

void DESFile::simulate()
{
    /// create Records that can be used as a step in time that will
    /// show queue and server state information
    for( auto& event : m_events)
    {

        if(event.type == 'A')
        {
            std::cout << "ARRIVAL" << std::endl;

            /// find the minimum queue

            /// if no server was available, add the event to a queue if possible, otherwise just discard the event

        }
        else if(event.type == 'D')
        {
            std::cout << "DEPARTURE" << std::endl;

            /// search for the event in the queues, if exists, then remove it
            /// and add the event to a server
        }
        else if(event.type == 'T')
        {
            std::cout << "TERMINATE" << std::endl;
            break;
        }

    }

}