#include "stdafx.h"
#include "printStructs.h"


/* Print the Event Type */
void printEventType(ETYPE e) 
{
	if (e == ARRIVAL)
		printf("type: ARRIVAL\n");
	else if (e == DEPARTURE)
		printf("type: DEPARTURE\n");
	else if (e == TERMINATE)
		printf("type: TERMINATE\n");
}

/* Print the Queue Type */
void printQueueType(QTYPE q) 
{
	if (q == FIFO)
		printf("type: FIFO\n");
	else if (q == LIFO)
		printf("type: LIFO\n");
}


/* Print the contents of an Event */
void printEvent(Event *e) 
{
	printf("=====================================\n");
	printf("id: %d\n", e->id);
	printf("entity: %d\n", e->entity);
	printEventType(e->type);
	printf("time: %f\n", e->time);
	printf("=====================================\n");
}


/* Print the contents of an Queue */
void printQueue(Queue *q)
{
	printf("=====================================\n");
	printf("capacity: %d\n", q->capacity);
	printf("total: %d\n", q->total);
	printQueueType(q->type);
	for (int i = 0; i < (int)q->events.size(); i++) 
	{
		printEvent(&q->events.at(i));
	}
	printf("=====================================\n");
}

/* Print the contents of an Server */
void printServer(Server *s) 
{
	printf("=====================================\n");
	printf("capacity: %d\n", s->capacity);
	printf("total: %d\n", s->total);
	for (int i = 0; i < (int)s->events.size(); i++)
	{
		printEvent(&s->events.at(i));
	}
	printf("=====================================\n");
}

/* Print the contents of an Event Handler */
void printEventHandler(EventHandler *eh) 
{
	printf("=====================================\n");
	for (int i = 0; i < (int)eh->events.size(); i++)
	{
		printEvent(&eh->events.at(i));
	}
	printf("=====================================\n");
}

/* Print the contents of an Record */
void printRecord(Record *r) 
{
	printf("=====================================\n");
	printf("id: %d\n", r->id);
	printf("time: %f\n", r->time);
	for (int i = 0; i < (int)r->queues.size(); i++) 
	{
		printQueue(&r->queues.at(i));
	}
	for (int i = 0; i < (int)r->servers.size(); i++) 
	{
		printServer(&r->servers.at(i));
	}
	printf("=====================================\n");
}

/* Print the System Information */
void printSystemInformation(System_Information *si) 
{
	printf("=====================================\n");
	printf("number of queues: %d\n", si->num_queues);
	printf("number of servers: %d\n", si->num_servers);
	printf("queue capacity: %d\n", si->queue_cap);
	printf("server capacity: %d\n", si->server_cap);
	printEventHandler(&si->handler);
	printf("=====================================\n");
}