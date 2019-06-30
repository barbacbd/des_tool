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

    if(!filename.isEmpty() && filename.endsWith(".json"))
    {
        m_filename = filename;
        read();
    }
}

DESFile::~DESFile()
{

}

void DESFile::read()
{
    /// NOTE: filename cannot be empty here, so we are not going to check

    /// Create, open, and read the file information to a variable
    QFile file(m_filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString data=file.readAll();
    file.close();
    parse(data);
}

void DESFile::parse(QString data)
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

        m_events.emplace_back(Event(entity.toStdString(), type, time));
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
        m_servers.emplace_back(DESServer(id.toStdString(), capacity, events));
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
        m_queues.emplace_back(DESQueue(id.toStdString(), capacity, events, type));
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