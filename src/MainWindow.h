/**
 * Author: Brent Barbachem
 * Date:   December 21, 2018
 *
 * Main Window class to hold all graphical information and display the
 * information so that the user can proceed through the simulation one step
 * at a time.
 */

#ifndef DES_TOOL_MAINWINDOW_H
#define DES_TOOL_MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QMenuBar>
#include <QWidget>
#include <QAction>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

    virtual ~MainWindow();

private:
    /**
     * Fill out the menu bar that will be displayed at the top of the main window
     */
    void createMenu();

    /**
     * Create an option that will be displayed under the menu as it is pressed by the user
     * @param menu - menu to add the option to
     * @param name - name of the menu option
     * @param slot - function linked to the opening of the option
     */
    void createMenuOption(QMenu *menu, QString name, const char *slot);

//    void readJsonDocument(QString filename);

private slots:
    /**
     * Callback function that will open a Dialog to allow user input for files
     */
    void onFileOpen();

    /**
     * Open a dialog to show the user some information about this program
     */
    void onAboutOpen();

private:

    QMenu *m_file_menu;

    QMenu *m_help_menu;

};


#endif //DES_TOOL_MAINWINDOW_H
