
#include "DESFile.h"


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
    QJsonArray order_array = events.toArray();

    for(QJsonArray::iterator it = order_array.begin(); it != order_array.end(); it++)
    {
        std::cout << "it = " << (*it).toString().toStdString() << std::endl;
    }
}

/// function to create servers
/// function to create queues