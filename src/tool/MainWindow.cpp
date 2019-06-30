
#include "MainWindow.h"
#include <QFileDialog>
#include <iostream>
#include "json/DESFile.h"
#include "simulation/Simulation.h"

MainWindow::MainWindow()
{
    createMenu();
}

MainWindow::~MainWindow()
{

}


void MainWindow::createMenuOption(QMenu *menu, QString name, const char *slot)
{
    if(!menu)
    {
        return; /// menu does not exist, fail!
    }

    /// Make the owner of this action this, so it should be cleaned up on close
    QAction *action = new QAction(this);
    action->setText(name);
    connect(action, SIGNAL(triggered()), this, slot);
    action->setEnabled(true);
    menu->addAction(action);
}

void MainWindow::createMenu()
{
    /// It was reported that the menu did not show up properly on MAC2
    /// adding this line to remove future osx issues
    menuBar()->setNativeMenuBar(false);

    /// File Menu
    m_file_menu = menuBar()->addMenu("File");
    createMenuOption(m_file_menu, "Open", SLOT(onFileOpen()));
    m_file_menu->addSeparator();
    createMenuOption(m_file_menu, "Quit", SLOT(close()));

    /// Help Menu
    m_help_menu = menuBar()->addMenu("Help");
    createMenuOption(m_help_menu, "About DES Tool", SLOT(onAboutOpen()));
}

void MainWindow::onFileOpen()
{
    QFileDialog fd(this);

    /// set the files to only be txt or json files since the
    /// ConfigCreator will only create these types of files
    fd.setNameFilter("*.json");

    if(QFileDialog::Accepted == fd.exec())
    {
        std::cout << "File = " << fd.selectedFiles().at(0).toStdString() << std::endl;

        /// process this file

        DESFile desFile = DESFile(fd.selectedFiles().at(0));
        Simulation sim = Simulation(desFile.getEvents(),
                desFile.getQueues(),
                desFile.getServers(),
                desFile.getEventOrder());
        sim.run();

        std::vector<Record> records = sim.getRecords();

        for(auto &r : records)
        {
            std::cout << r.toString() << std::endl;
        }

    }

}

void MainWindow::onAboutOpen()
{
    /// open a dialog that prints out some information about our program
}

//void MainWindow::readJsonDocument(QString filename)
//{
//    /// Create, open, and read the file information to a variable
//    QFile file(filename);
//    file.open(QIODevice::ReadOnly | QIODevice::Text);
//    QString data = file.readAll();
//    file.close();
//
//    /// convert the string to a json document and get the first object {}
//    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
//    QJsonObject json = doc.object();
//
//    /// if the json document is valid then we should attempt to read the data that
//    /// we are concerned with
//
//    if(json.isEmpty())
//    {
//#ifdef _DEBUG
//        std::cout << "Failed to open the json object from file: " << filename.toStdString() << std::endl;
//#endif
//        return;
//    }
//
//    std::map<QString, QJsonValue> json_values;
//
//    QStringList object_keys = json.keys();
//    for(auto key : object_keys)
//    {
////        json_values[key] = json[key];
//
//        std::cout << "Key = " << key.toStdString() << " type = " << (int)json[key].type() << std::endl;
//    }
//
//
////    QJsonArray jsonArray = jsonObject["properties"].toArray();
////
////    foreach (const QJsonValue & value, jsonArray) {
////        QJsonObject obj = value.toObject();
////        propertyNames.append(obj["PropertyName"].toString());
////        propertyKeys.append(obj["key"].toString());
////    }
//}