/**
 * Autbor: Brent Barbachem
 * Date:   December 22, 2018
 *
 * Class to wrap the Qt Json File. This file will read in the json document
 * and parse the information that is specific to our DES tool.
 */

#ifndef DES_TOOL_DESFILE_H
#define DES_TOOL_DESFILE_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QStringList>
#include <QFile>

class DESFile
{
public:
    /**
     * @param filename [optional] - name of the file that will be parsed if it is not empty
     */
    DESFile(QString filename = "");

    /**
     * Destructor for this file
     */
    ~DESFile();

    /**
     * If the filename was empty, then use this filename. The member function will NOT allow the user to set
     * a new filename.
     * @param filename - filename to use
     */
    void setFilename(QString filename);

    /**
     * If the filename is set, open the file, read all contents and store the
     * Qt Json Object
     */
    void read();

    /**
     * Search for the name in the object
     * @param name - name to search for in the json document
     * @return QJsonValue, empty value if the document is empty
     */
    QJsonValue getJsonValue(QString name);

private:

    /**
     *
     * @param events
     * @param order
     */
    void orderEvents(QJsonValue events, QJsonValue order);

private:
    QJsonDocument m_doc;

    QString m_filename;

};


#endif //DES_TOOL_DESFILE_H
