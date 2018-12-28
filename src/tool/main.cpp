/**
 * Author: Brent Barbachem
 * Date:   December 21, 2018
 *
 * Main Window is created and run through the main thread of execution
 */

#include <QApplication>
#include "MainWindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MainWindow window;
    window.setMinimumSize(800, 600);
    window.show();

    return app.exec();
}