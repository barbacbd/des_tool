#include "stdafx.h"
#include "utility.h"

/* Copy the queues */
void copyQueues(std::vector<Queue> &from, std::vector<Queue> &to) 
{
	for (int i = 0; i < (int)from.size(); i++) 
	{
		Queue q;
		for (int j = 0; j < from.at(i).events.size(); j++) 
		{
			q.events.push_back(from.at(i).events.at(j));
		}
		to.push_back(q);
	}
}

/* Copy the Servers */
void copyServers(std::vector<Server> &from, std::vector<Server> &to) 
{
	for (int i = 0; i < (int)from.size(); i++) {
		Server s;
		for (int j = 0; j < from.at(i).events.size(); j++) 
		{
			s.events.push_back(from.at(i).events.at(j));
		}
		to.push_back(s);
	}
}


/*
* Find the "Next" Event of given type in the
* EventHandler
*/
bool nextEvent(EventHandler *eh, Event &e, ETYPE type, int id) 
{
	/* The EventHandler is kept current so we
	*  can start from the beginning
	*/
	for (int i = id+1; i <= getTermination(&info); i++) 
	{
		if (eh->events.at(i).type == type)
		{
			e = eh->events.at(i); /* set the event */
			return true; /* SUCCESS */
		}
	}
	return false; /* Fail */
}

/* get all of the next events and put them into the record */
void getNextEventList(Record *r, EventHandler *eh) 
{
	Event arrival, departure, terminate, fake;

	fake.entity = fake.id = fake.time = -1;

	if (nextEvent(eh, arrival, ARRIVAL, r->id))
		r->next_list.push_back(arrival);
	else
		r->next_list.push_back(fake);

	if (nextEvent(eh, departure, DEPARTURE, r->id))
		r->next_list.push_back(departure);
	else
		r->next_list.push_back(fake);

	if (nextEvent(eh, terminate, TERMINATE, r->id))
		r->next_list.push_back(terminate);
	else
		r->next_list.push_back(fake);
}

/*
* Return the position of the queue with the
* lowest amount of entries.
*/
int minQueue(System_Information *info) 
{
	int smallest_total = info->queue_cap;
	int pos = -1;
	for (int i = 0; i < info->num_queues; i++) 
	{
		int tot = (int)info->queues.at(i).events.size();
		if (tot < smallest_total) 
		{
			pos = i;
			smallest_total = tot;
		}
	}

	return pos;
}

/*
* Return the position of the server with the
* lowest amount of entries
*/
int minServer(System_Information *info) 
{
	int smallest_total = info->server_cap;
	int pos = -1;
	for (int i = 0; i < info->num_servers; i++) 
	{
		int tot = info->servers.at(i).total;
		if (tot < smallest_total) 
		{
			pos = i;
			smallest_total = tot;
		}
	}

	return pos;
}


/*
* Remove the event from the server if it exists
*/
bool removeEvent(System_Information *info, Event e) 
{
	for (int i = 0; i < info->num_servers; i++) {
		for (int j = 0; j < (int)info->servers.at(i).events.size(); j++)
		{
			if (info->servers.at(i).events.at(j).entity == e.entity) 
			{
				info->servers.at(i).events.erase(
					info->servers.at(i).events.begin() + j);
				info->servers.at(i).total--;
				return true;
			}
		}
	}
	return false;
}


/*
* Compare the types against each other
*
* Return -1 for E.type < F.type
*         0 for E.Type == F.type
*         1 for E.Type > F.type
*/
int compareType(ETYPE E, ETYPE F, int *event_order)
{
	int e_type = event_order[E];
	int f_type = event_order[F];

	if (e_type == f_type) return 0;
	else return (e_type < f_type) ? -1 : 1;
}

/*
* Set the events in the correct order based on the
* order of events structure that the user has provided.
* This function will handle any ties in time so that the
* simulation function can sequentially process events.
*/
void orderEvents(System_Information *info) 
{
	bool swapped = true;
	int j = 0;
	Event tmp;
	std::vector<Event> events = info->handler.events;

	while (swapped) {
		swapped = false;
		j++;
		for (int i = 0; i < (int)events.size() - j; i++)
		{
			if (events.at(i).time == events.at(i + 1).time) 
			{
				int compare = compareType(events.at(i).type,
					events.at(i + 1).type, info->event_order);

				if (compare > 0) 
				{
					tmp = events.at(i);
					events.at(i) = events.at(i + 1);
					events.at(i + 1) = tmp;
					swapped = true;
				}
			}
			else 
			{
				if (events.at(i).time > events.at(i + 1).time)
				{
					tmp = events.at(i);
					events.at(i) = events.at(i + 1);
					events.at(i + 1) = tmp;
					swapped = true;
				}
			}
		}
	}
	info->handler.events = events;
}

/* Return the position of the event in the events list */
int findEvent(EventHandler eh, Event e) 
{
	for (int i = 0; i < (int)eh.events.size(); i++)
	{
		if (eh.events.at(i).id == e.id)
			return i;
	}
	return -1;
}

/* get the event position that is the termination */
int getTermination(System_Information * info) {
	for (int i = 0; i < (int)info->handler.events.size(); i++) 
	{
		if (info->handler.events.at(i).type == TERMINATE)
			return i;
	}
	return -1; /* error no terminate found */
}

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

/* Add an Event to the Queue in the correct order */
void addEventToQueue(Queue &q, Event e, QTYPE type)
{
	if (type == FIFO) 
	{
		q.events.push_back(e);
		q.total++;
	}
	else if (type == LIFO)
	{
		q.events.insert(q.events.begin(), e);
		q.total++;
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

		/* Set all record information */
		getNextEventList(&r, &info->handler);

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


/* change the color values for the color passed in */
void change_color(color &c, float r, float g, float b) 
{
	c.r = r; /* set the red component */
	c.g = g; /* set the green component */
	c.b = b; /* set the blue component */
}

/* similar function to recolor an arrow */
void auto_color(arrow &a, int x, int y, float r, float g, float b) 
{
	if (r > 1.0 || r < 0.0 || g > 1.0 || g < 0.0 || b > 1.0 || b < 0.0)
		return;

	if (in_arrow(a, x, y))
		change_color(a.b.c, r, g, b);
	else
		change_color(a.b.c, 1.0, 1.0, 1.0);
}

/* automatically change the color of the button */
void auto_color(button &btn, int x, int y, float r, float g, float b) 
{
	if (r > 1.0 || r < 0.0 || g > 1.0 || g < 0.0 || b > 1.0 || b < 0.0)
		return;

	if (in_button(btn, x, y))
		change_color(btn.c, r, g, b);
	else
		change_color(btn.c, 1.0, 1.0, 1.0);
}

void check_mouse_pos(int x, int y)
{
	/* check the quit button at all states */
	auto_color(quit, x, y, 1.0, 0.0, 0.0);

	if (state == INITIAL) 
	{
		auto_color(start, x, y, 0.0, 1.0, 0.0);
		auto_color(cont, x, y, 0.0, 1.0, 0.0);
	}
	else if (state == HOME) 
	{
		// draw home screen information
		auto_color(prev, x, y, 0.0, 1.0, 0.0);
		auto_color(next, x, y, 0.0, 1.0, 0.0);
		auto_color(home, x, y, 1.0, 0.0, 0.0);
		auto_color(stats, x, y, 0.5, 0.5, 0.0);
		auto_color(all_events, x, y, 0.0, 0.5, 0.5);
		auto_color(queues, x, y, 0.0, 0.0, 1.0);
		auto_color(servers, x, y, 0.0, 0.0, 1.0);
	}
	else if (state == ALL_EVENTS)
	{
		auto_color(back, x, y, 1.0, 0.0, 0.0);
		auto_color(up, x, y, 0.0, 1.0, 0.0);
		auto_color(down, x, y, 0.0, 1.0, 0.0);
	}
	else if (state == QUEUES) 
	{
		auto_color(up, x, y, 0.0, 1.0, 0.0);
		auto_color(down, x, y, 0.0, 1.0, 0.0);
		auto_color(back, x, y, 1.0, 0.0, 0.0);
	}
	else if (state == SERVERS) 
	{
		auto_color(up, x, y, 0.0, 1.0, 0.0);
		auto_color(down, x, y, 0.0, 1.0, 0.0);
		auto_color(back, x, y, 1.0, 0.0, 0.0);
	}
	else if (state == STATS) 
	{
		auto_color(back, x, y, 1.0, 0.0, 0.0);
		auto_color(generate_report, x, y, 0.0, 1.0, 1.0);
	}
}

/* try to select the button */
void select(int x, int y)
{
	if (in_button(quit, x, y)) exit(0);

	switch (state) 
	{
	case INITIAL:

		if (in_button(start, x, y)) 
		{
			state = HOME;
			// reset the current position in the events
			sim_pos = 0;
		}
		else if (in_button(cont, x, y))
		{
			state = HOME;
			// dont reset the current position to 0
		}
		break;
	case HOME:
		if (in_button(all_events, x, y)) state = ALL_EVENTS;
		else if (in_button(home, x, y)) state = INITIAL;
		else if (in_button(queues, x, y)) state = QUEUES;
		else if (in_button(servers, x, y)) state = SERVERS;
		else if (in_button(stats, x, y)) state = STATS;
		else if (in_button(prev, x, y))
		{
			// change to the previous event -- if we can 
			if (sim_pos > 0)
				sim_pos--;
		}
		else if (in_button(next, x, y))
		{
			// change to the next event -- if we can
			if (sim_pos < getTermination(&info))
				sim_pos++;
		}
		break;
	case ALL_EVENTS:
		if (in_button(back, x, y))
		{
			state = HOME;
			curr_start = 0;
		}
		else if (in_arrow(up, x, y))
		{
			if (curr_start > 0)
				curr_start --;
		}
		else if (in_arrow(down, x, y))
		{
			float h = winHeight * 0.85 - 60.0;
			int npp = h / 25; // num per page

			if((curr_start + npp) < (int)info.handler.events.size())
				curr_start++;
		}
		break;
	case QUEUES:
		if (in_button(back, x, y))
		{
			state = HOME;
			curr_start = 0;
		}
		else if (in_arrow(up, x, y)) 
		{
			if (curr_start > 0)
				curr_start -= 3;
		}
		else if (in_arrow(down, x, y)) 
		{
			if (curr_start < info.num_queues - 9)
				curr_start += 3;
		}
		break;
	case SERVERS:
		if (in_button(back, x, y)) 
		{
			state = HOME;
			curr_start = 0;
		}
		else if (in_arrow(up, x, y)) 
		{
			if (curr_start > 0)
				curr_start -= 3;
		}
		else if (in_arrow(down, x, y)) 
		{
			if (curr_start < info.num_servers - 9)
				curr_start += 3;
		}
		break;
	case STATS:
		if (in_button(back, x, y)) state = HOME;
		else if (in_button(generate_report, x, y))
		{
			if (sim_pos >= getTermination(&info))
			{
				generate_reports(&info);
			}
		}
		break;

	}
}

/* common function for printing information on the screen */
void printToScreen(char text[300], float x, float y)
{
	int len = (int)strlen(text);
	glRasterPos2f(x, y);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
}