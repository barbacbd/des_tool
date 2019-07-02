/**
 * Author: Brent Barbachem
 * Date:   6/30/19.
 */

#ifndef DESTOOL_MAINWIDGET_H
#define DESTOOL_MAINWIDGET_H


#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QTableWidget>
#include "../components/Components.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    MainWidget(QWidget *parent = NULL);

    void setInfo(std::vector<Event> events, std::vector<Record> records);

private slots:
    void previousEvent();

    void nextEvent();

    void queueChanged();
    void serverChanged();

protected:
    void init();

    void updateCurrentEvent();

    void updateCurrentQueues();
    void updateCurrentServers();

    void update();



private:

    QListWidget *m_queues;
    QListWidget *m_queue_events;

    QListWidget *m_servers;
    QListWidget *m_server_events;

    QTableWidget *m_current_event;

    QPushButton *m_prev_button;
    QPushButton *m_next_button;

    int m_current_index;

    std::vector<Event> m_events;
    std::vector<Record> m_records;
};

#endif //DESTOOL_MAINWIDGET_H
