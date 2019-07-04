/**
 * Author: Brent Barbachem
 * Date:   6/30/19.
 */

#include "MainWidget.h"
#include <QGridLayout>
#include <QCommonStyle>
#include <QHeaderView>


MainWidget::MainWidget(QWidget *parent) 
  : QWidget(parent), m_current_index(0), m_current_queue_row(-1), m_current_server_row(-1)
{
    init();
}

void MainWidget::init()
{
    /// QStyle::SP_Arrow_Left
    /// QStyle::SP_Arrow_Right

    QGridLayout *layout = new QGridLayout;

    m_current_event = new QTableWidget(this);
    m_current_event->setColumnCount(3);
    m_current_event->setRowCount(1);

    /// Hide the table widget verical header
    auto *vertical_header = new QHeaderView(Qt::Vertical);
    vertical_header->hide();
    m_current_event->setVerticalHeader(vertical_header);

    m_current_event->setHorizontalHeaderItem(0, new QTableWidgetItem("Event ID"));
    m_current_event->setHorizontalHeaderItem(1, new QTableWidgetItem("Event Type"));
    m_current_event->setHorizontalHeaderItem(2, new QTableWidgetItem("Time"));

    layout->addWidget(m_current_event, 1, 1, 1, 2);

    QCommonStyle next_style;
    m_next_button = new QPushButton("", this);
    m_next_button->setIcon(next_style.standardIcon(QStyle::SP_ArrowRight));
    connect(m_next_button, SIGNAL(released()), this, SLOT(nextEvent()));

    QCommonStyle back_style;
    m_prev_button = new QPushButton("", this);
    m_prev_button->setIcon(next_style.standardIcon(QStyle::SP_ArrowLeft));
    connect(m_prev_button, SIGNAL(released()), this, SLOT(previousEvent()));

    layout->addWidget(m_prev_button, 3, 1, 1, 1);
    layout->addWidget(m_next_button, 3, 2, 1, 1);

    m_queues = new QListWidget(this);
    connect(m_queues, SIGNAL(itemSelectionChanged()), this, SLOT(queueChanged()));
    m_servers = new QListWidget(this);
    connect(m_servers, SIGNAL(itemSelectionChanged()), this, SLOT(serverChanged()));

    layout->addWidget(m_queues, 4, 1, 3, 2);
    layout->addWidget(m_servers, 7, 1, 3, 2);

    m_queue_events = new QListWidget(this);
    m_server_events = new QListWidget(this);

    layout->addWidget(m_queue_events, 4, 4, 3, 2);
    layout->addWidget(m_server_events, 7, 4, 3, 2);

    updateCurrentEvent();

    setLayout(layout);
}

void MainWidget::updateCurrentEvent()
{
    if(m_events.empty())
    {
        return;
    }

    if(m_current_event->item(0, 0))
    {
        m_current_event->item(0, 0)->setText(QString(QString::fromStdString(m_events[m_current_index].getID())));
    }
    else
    {
        QTableWidgetItem *id_item = new QTableWidgetItem(
                QString(QString::fromStdString(m_events[m_current_index].getID())));
        id_item->setFlags(id_item->flags() ^ Qt::ItemIsEditable);
        m_current_event->setItem(0, 0, id_item);
    }


    QString type = "";
    switch(m_events[m_current_index].getType())
    {
        case ARRIVAL: type = "ARRIVAL"; break;
        case DEPARTURE: type = "DEPARTURE"; break;
        case TERMINATE: type = "TERMINATE";  break;
    }

    if(m_current_event->item(0, 1))
    {
        m_current_event->item(0,1)->setText(type);
    }
    else
    {
        QTableWidgetItem *type_item = new QTableWidgetItem(type);
        type_item->setFlags(type_item->flags() ^ Qt::ItemIsEditable);
        m_current_event->setItem(0, 1, type_item);
    }

    if(m_current_event->item(0, 2))
    {
        m_current_event->item(0, 2)->setText(QVariant(m_events[m_current_index].getTime()).toString());
    }
    else
    {
        QTableWidgetItem *time_item = new QTableWidgetItem(QVariant(m_events[m_current_index].getTime()).toString());
        time_item->setFlags(time_item->flags() ^ Qt::ItemIsEditable);
        m_current_event->setItem(0, 2, time_item);
    }

}

void MainWidget::updateCurrentQueues()
{
    m_queues->clear();

    if(m_current_index < m_records.size())
    {
        for(auto &q : m_records[m_current_index].getQueues())
        {
            QString type = (q.getType() == FIFO) ? "FIFO" : "LIFO";

            QString queue_info = "QUEUE: " + QString::fromStdString(q.getID()) + " " + type;
            m_queues->addItem(new QListWidgetItem(queue_info));
        }
    }
}

void MainWidget::updateCurrentServers()
{
    m_servers->clear();

    if(m_current_index < m_records.size())
    {
        for(auto &q : m_records[m_current_index].getServers())
        {
            QString server_info = "Server: " + QString::fromStdString(q.getID());
            m_servers->addItem(new QListWidgetItem(server_info));
        }
    }
}

void MainWidget::setInfo(std::vector<Event> events, std::vector<Record> records)
{
    m_events = events;
    m_records = records;
    m_current_index = 0;

    update();
}

void MainWidget::previousEvent()
{
    if(m_events.empty() || m_records.empty())
    {
        return;
    }

    if(m_current_index > 0 )
    {
        m_current_index--;
    }

    update();
}

void MainWidget::nextEvent()
{
    if(m_events.empty())
    {
        return;
    }

    if(m_events[m_current_index].getType() != TERMINATE && m_current_index < m_events.size())
    {
        m_current_index ++;
    }

    update();
}

void MainWidget::update()
{
    updateCurrentEvent();
    updateCurrentQueues();
    updateCurrentServers();
    updateQueueEvents();
    updateServerEvents();
}

void MainWidget::queueChanged()
{
    m_current_queue_row = m_queues->currentRow();

    updateQueueEvents();
}

void MainWidget::updateQueueEvents()
{
    if(m_current_queue_row < 0)
    {
        return;
    }

    m_queue_events->clear();

    for(auto &e : m_records[m_current_index].getQueues()[m_current_queue_row].getEvents())
    {
        QString event_info = "Event: " + QString::fromStdString(e.getID()) + " : " + QVariant(e.getTime()).toString();
        m_queue_events->addItem(new QListWidgetItem(event_info));
    }
}

void MainWidget::serverChanged()
{
    m_current_server_row = m_servers->currentRow();

    updateServerEvents();
}

void MainWidget::updateServerEvents()
{
    if(m_current_server_row < 0)
    {
        return;
    }

    m_server_events->clear();

    for(auto &e : m_records[m_current_index].getServers()[m_current_server_row].getEvents())
    {
        QString event_info = "Event: " + QString::fromStdString(e.getID()) + " : " + QVariant(e.getTime()).toString();
        m_server_events->addItem(new QListWidgetItem(event_info));
    }
}
