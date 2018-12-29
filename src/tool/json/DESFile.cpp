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
    QString data = file.readAll();
    file.close();

    /// convert the string to a json document and get the first object {}
    m_doc = QJsonDocument::fromJson(data.toUtf8());

    QJsonValue events = getJsonValue("EVENTS");
    QJsonValue order = getJsonValue("EVENT_ORDER");
    if(events.isArray() && order.isArray())
    {
        orderEvents(events, order);
    }

//    QJsonValue servers = getJsonValue("SERVERS");
//    if(servers.isArray())
//    {
//        createServers(servers);
//    }
//
//
//    QJsonValue queues = getJsonValue("QUEUES");
//    if(queues.isArray())
//    {
//        createQueues(queues);
//    }
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
        int type;

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
            QString str = typeValue.toString();
            std::map<QChar, int>::iterator it = m_event_types.find(str.at(0));
            if(it != m_event_types.end())
            {
                type = it->second;
            }
        }

        m_events.push_back({entity, type, time});
    }

    /// sort the events based on time and type
    std::sort(m_events.begin(), m_events.end(), std::bind(&DESFile::compareEvents, this, std::placeholders::_1, std::placeholders::_2));

//    for(Event e : m_events)
//    {
//        std::cout << e.id.toStdString() << " " << e.type << " " << e.time << std::endl;
//    }
}

bool DESFile::compareEvents(const Event &a, const Event &b)
{
    if(a.time < b.time)
    {
        return true;
    }
    else if(a.time == b.time)
    {
        return a.type <= b.type;
    }
    else
    {
        return false;
    }
}

/// function to create servers
/// function to create queues