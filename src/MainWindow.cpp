
#include "MainWindow.h"
#include <QFileDialog>
#include <iostream>

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

    /// if we want to, we could set a filter on the types of files that we want
    /// the user to bring into the program here

    if(QFileDialog::Accepted == fd.exec())
    {
        std::cout << "File = " << fd.selectedFiles().at(0).toStdString() << std::endl;

        /// process this file

    }

}

void MainWindow::onAboutOpen()
{
    /// open a dialog that prints out some information about our program
}