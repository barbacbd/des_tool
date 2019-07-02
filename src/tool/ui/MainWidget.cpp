/**
 * Author: Brent Barbachem
 * Date:   6/30/19.
 */

#include "MainWidget.h"
#include <QGridLayout>
#include <QCommonStyle>
#include <QHeaderView>


MainWidget::MainWidget(QWidget *parent) : QWidget(parent), m_current_index(0)
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

    layout->addWidget(m_current_event, 1, 1, 1, 3);

    QCommonStyle next_style;
    m_next_button = new QPushButton("", this);
    m_next_button->setIcon(next_style.standardIcon(QStyle::SP_ArrowRight));
    connect(m_next_button, SIGNAL(released()), this, SLOT(nextEvent()));

    QCommonStyle back_style;
    m_prev_button = new QPushButton("", this);
    m_prev_button->setIcon(next_style.standardIcon(QStyle::SP_ArrowLeft));
    connect(m_prev_button, SIGNAL(released()), this, SLOT(previousEvent()));

    layout->addWidget(m_prev_button, 3, 1, 1, 1);
    layout->addWidget(m_next_button, 3, 3, 1, 1);

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

void MainWidget::setInfo(std::vector<Event> events, std::vector<Record> records)
{
    m_events = events;
    m_records = records;
    m_current_index = 0;

    updateCurrentEvent();
}

void MainWidget::previousEvent()
{
    if(m_events.empty())
    {
        return;
    }

    if(m_current_index > 0 )
    {
        m_current_index--;
    }

    updateCurrentEvent();
}

void MainWidget::nextEvent()
{
    if(m_events.empty())
    {
        return;
    }

    if(m_events[m_current_index].getType() != TERMINATE && m_current_index < m_events.size() - 1)
    {
        m_current_index ++;
    }

    updateCurrentEvent();
}