#include "utility.h"


///*
//* Find the "Next" Event of given type in the
//* EventHandler
//*/
//bool nextEvent(EventHandler *eh, Event &e, ETYPE type, int id)
//{
//	/* The EventHandler is kept current so we
//	*  can start from the beginning
//	*/
//	for (int i = id+1; i <= getTermination(&info); i++)
//	{
//		if (eh->events.at(i).type == type)
//		{
//			e = eh->events.at(i); /* set the event */
//			return true; /* SUCCESS */
//		}
//	}
//	return false; /* Fail */
//}

///* get all of the next events and put them into the record */
//void getNextEventList(Record *r, EventHandler *eh)
//{
//	Event arrival, departure, terminate, fake;
//
//	fake.entity = fake.id = fake.time = -1;
//
//	if (nextEvent(eh, arrival, ARRIVAL, r->id))
//		r->next_list.push_back(arrival);
//	else
//		r->next_list.push_back(fake);
//
//	if (nextEvent(eh, departure, DEPARTURE, r->id))
//		r->next_list.push_back(departure);
//	else
//		r->next_list.push_back(fake);
//
//	if (nextEvent(eh, terminate, TERMINATE, r->id))
//		r->next_list.push_back(terminate);
//	else
//		r->next_list.push_back(fake);
//}

///*
//* Remove the event from the server if it exists
//*/
//bool removeEvent(System_Information *info, Event e)
//{
//	for (int i = 0; i < info->num_servers; i++) {
//		for (int j = 0; j < (int)info->servers.at(i).events.size(); j++)
//		{
//			if (info->servers.at(i).events.at(j).entity == e.entity)
//			{
//				info->servers.at(i).events.erase(
//					info->servers.at(i).events.begin() + j);
//				info->servers.at(i).total--;
//				return true;
//			}
//		}
//	}
//	return false;
//}


///* Return the position of the event in the events list */
//int findEvent(EventHandler eh, Event e)
//{
//	for (int i = 0; i < (int)eh.events.size(); i++)
//	{
//		if (eh.events.at(i).id == e.id)
//			return i;
//	}
//	return -1;
//}


/* get the event from the queue */
bool getEventFromQueue(System_Information * info, Event &e) 
{
	e.time = (info->q_type == FIFO) ? std::numeric_limits<float>::max() : -1;
	int pos = -1;

	for (int i = 0; i < info->queues.size(); i++) 
	{
		if ((int)info->queues.at(i).events.size() > 0)
		{
			if ((info->q_type == FIFO &&
				info->queues.at(i).events.at(0).time < e.time) ||
				(info->q_type == LIFO &&
					info->queues.at(i).events.at(0).time > e.time))
			{
				e = info->queues.at(i).events.at(0);
				pos = i;
			}
		}
	}

	if (pos == -1) return false; /* Error OR no events in the queue */
	else 
	{
		info->queues.at(pos).events.erase(info->queues.at(pos).events.begin());
		info->queues.at(pos).total--;
		return true;
	}
}

/* Move the elements to the server from the queue if we can */
void queueToServer(System_Information *info) 
{
	int mq;
	int ms = minServer(info);
	if (ms > -1) 
	{ /* there is a server with room */ 
		mq = minQueue(info);
		if (mq > -1) 
		{ /* there is a queue with events */
			Event e;
			if (getEventFromQueue(info, e)) 
			{
				info->servers.at(ms).events.push_back(e);
				info->servers.at(ms).total++;
			}
		}
	}

}

/*
* Create all of the records at each time step for the simulation
*/
void createRecords(System_Information *info) 
{
	/* make sure that our events are in order */
	//orderEvents(info);

	for (int i = 0; i < (int)info->handler.events.size(); i++) 
	{
		Record r; /* create a new [local] record */
		Event e = info->handler.events.at(i); /* local Event */

		r.id = i;
		r.time = e.time;

		if (e.type == ARRIVAL) 
		{
			/* indicate the event occured */
			info->handler.events.at(i).occurred = true;

			int server = minServer(info);
			if (server > -1) 
			{ /* found a server */ 
				info->servers.at(server).events.push_back(e);
				info->servers.at(server).total++;
			}
			else 
			{
				int queue = minQueue(info);
				if (queue > -1) { /* found a queue */
					addEventToQueue(info->queues.at(queue), e, info->q_type);
				}
				else /* delete the event */
					removeEvent(info, e);
			}
		}

		else if (e.type == DEPARTURE) 
		{
			//
			// May be removed since the Event is deleted
			//

			/* indicate that the event occured */
			info->handler.events.at(i).occurred = true;

			bool found = removeEvent(info, e);
			if (!found)
			{ /* Error - no event found */
				printf("ERROR - Event %d not found in a server.\n", e.entity);
				break;
			}
			else 
			{
				/* Add the next event to the open server */
				queueToServer(info);
			}
		}

//		/* Set all record information */
//		getNextEventList(&r, &info->handler);

            r.time = e.time;
            r.id = i;
            r.queues = info->queues;
            r.servers = info->servers;

		/* add the record to the list */
		info->records.push_back(r);

		if (e.type == TERMINATE)
			break; /* Terminate Event */
	}
}
