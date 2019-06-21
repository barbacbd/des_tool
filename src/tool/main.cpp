/**
 * Author: Brent Barbachem
 * Date:   December 21, 2018
 *
 * Main Window is created and run through the main thread of execution
 */

#include <QApplication>
#include "MainWindow.h"
#include <QFile>
#include <QTextStream>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MainWindow window;
    window.setMinimumSize(800, 600);
    window.show();

    QFile f(":qdarkstyle/style.qss");
    if (!f.exists())
    {
        printf("Unable to set stylesheet, file not found\n");
    }
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        app.setStyleSheet(ts.readAll());
    }
    
    return app.exec();
}


