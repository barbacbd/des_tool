#include "stdafx.h"
#include "draw.h"

/********************** BEGIN PRIVATE INTERNAL FUNCTIONS *********************/

/* draw the arrow button with the correct color */
void _draw_arrow(arrow a)
{
	glColor3f(a.b.c.r, a.b.c.g, a.b.c.b);

	glBegin(GL_TRIANGLES);
	if (a.dir == 0)
	{ // face up
		glVertex3f(a.b.xmin, a.b.ymin, 0.0);
		glVertex3f((a.b.xmax + a.b.xmin) / 2.0, a.b.ymax, 0.0);
		glVertex3f(a.b.xmax, a.b.ymin, 0.0);
	}
	else
	{ // face down
		glVertex3f(a.b.xmin, a.b.ymax, 0.0);
		glVertex3f((a.b.xmax + a.b.xmin) / 2.0, a.b.ymin, 0.0);
		glVertex3f(a.b.xmax, a.b.ymax, 0.0);
	}
	glEnd();
}

/* draw the button with the correct color */
void _draw_button(button b)
{
	glColor3f(b.c.r, b.c.g, b.c.b);
	glBegin(GL_POLYGON);
	glVertex3f(b.xmin, b.ymin, 0.0);
	glVertex3f(b.xmin, b.ymax, 0.0);
	glVertex3f(b.xmax, b.ymax, 0.0);
	glVertex3f(b.xmax, b.ymin, 0.0);
	glEnd();

	std::stringstream ss((std::string)b.text);
	std::string item;
	std::vector<std::string> tokens;
	while (getline(ss, item, '-'))
	{
		tokens.push_back(item);
	}

	float pos = 0.0;
	for (int j = 0; j < (int)tokens.size(); j++)
	{
		const char * tmp = tokens.at(j).c_str();

		int width = 0;
		int len = (int)strlen(tmp);
		for (int i = 0; i < len; i++)
		{
			width += glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, tmp[i]);
		}

		if (width > 0)
		{
			glColor3f(0.0, 0.0, 0.0); 	/* black text */
			glRasterPos2f(((b.xmax + b.xmin - width) / 2.0), (b.ymax + b.ymin) / 2.0 - pos);

			for (int i = 0; i < len; i++)
			{
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, tmp[i]);
			}
		}
		pos += 20.0;
	}
}

/* Draw the queues - maximum of 3 per line */
void _draw_all_servers(System_Information *info, int curr_start)
{
	float qw = winWidth / 4;
	float qh = (winHeight * 0.85);
	char text[300];

	int start_h = winHeight * 0.85;
	start_h -= qh / 24.0;

	Record r = info->records.at(sim_pos);

	// need to take the back and quit buttons into account 
	// height and width will mimic th style below
	// 1/24 --- 1/4 --- 1/12 --- 1/4 --- 1/12 --- 1/4 --- 1/24
	int draw_max = 0;
	if (curr_start + 9 > info->num_servers)
		draw_max = info->num_servers;
	else
		draw_max = curr_start + 9;

	for (int i = curr_start; i < draw_max; i += 3)
	{
		// draw the first three - if we can
		int count = draw_max - i;
		float start_w = winWidth / 24.0;

		for (int j = 0; j < count; j++)
		{
			glColor3f(1.0, 1.0, 1.0); /* white color */
			glBegin(GL_POLYGON);
			glVertex3f(start_w, start_h, 0.0);
			glVertex3f(start_w, start_h - qh / 4.0, 0.0);
			glVertex3f(start_w + winWidth / 4.0, start_h - qh / 4.0, 0.0);
			glVertex3f(start_w + winWidth / 4.0, start_h, 0.0);
			glEnd();

			glColor3f(0.0, 0.0, 0.0); 	/* black text */
			snprintf(text, 300, "Server:");
			printToScreen(text, start_w, start_h - qh / 16.0);

			snprintf(text, 300, "%d", i + j + 1);
			printToScreen(text, start_w + winWidth / 6, start_h - qh / 16.0);

			snprintf(text, 300, "Capacity:");
			printToScreen(text, start_w, start_h - qh / 16.0 - 20.0);

			snprintf(text, 300, "%d", r.servers.at(i + j).capacity);
			printToScreen(text, start_w + winWidth / 6.0, start_h - qh / 16.0 - 20.0);

			snprintf(text, 300, "Total:");
			printToScreen(text, start_w, start_h - qh / 16.0 - 40);

			snprintf(text, 300, "%d", r.servers.at(i + j).total);
			printToScreen(text, start_w + winWidth / 6.0, start_h - qh / 16.0 - 40);

			start_w += winWidth / 3;
		}
		start_h -= qh / 3;
	}
}


/* Draw the queues - maximum of 3 per line */
void _draw_all_queues(System_Information *info, int curr_start)
{
	char text[300];
	float qw = winWidth / 4;
	float qh = (winHeight * 0.85);

	int start_h = winHeight * 0.85;
	start_h -= qh / 24.0;

	Record r = info->records.at(sim_pos);

	// need to take the back and quit buttons into account 
	// height and width will mimic th style below
	// 1/24 --- 1/4 --- 1/12 --- 1/4 --- 1/12 --- 1/4 --- 1/24
	int draw_max = 0;
	if (curr_start + 9 > info->num_queues)
		draw_max = info->num_queues;
	else
		draw_max = curr_start + 9;

	for (int i = curr_start; i < draw_max; i += 3)
	{
		// draw the first three - if we can
		int count = draw_max - i;
		float start_w = winWidth / 24.0;

		for (int j = 0; j < count; j++)
		{
			glColor3f(1.0, 1.0, 1.0); /* white color */
			glBegin(GL_POLYGON);
			glVertex3f(start_w, start_h, 0.0);
			glVertex3f(start_w, start_h - qh / 4.0, 0.0);
			glVertex3f(start_w + winWidth / 4.0, start_h - qh / 4.0, 0.0);
			glVertex3f(start_w + winWidth / 4.0, start_h, 0.0);
			glEnd();

			glColor3f(0.0, 0.0, 0.0); 	/* black text */
			// draw the information about the queue
			snprintf(text, 300, "Queue:");
			printToScreen(text, start_w, start_h - qh / 16.0);

			snprintf(text, 300, "%d", i + j + 1);
			printToScreen(text, start_w + winWidth / 6.0, start_h - qh / 16.0);

			snprintf(text, 300, "Capacity:");
			printToScreen(text, start_w, start_h - qh / 16.0 - 20.0);

			snprintf(text, 300, "%d", r.queues.at(i + j).capacity);
			printToScreen(text, start_w + winWidth / 6.0, start_h - qh / 16.0 - 20.0);

			snprintf(text, 300, "Total:");
			printToScreen(text, start_w, start_h - qh / 16.0 - 40);

			snprintf(text, 300, "%d", r.queues.at(i + j).total);
			printToScreen(text, start_w + winWidth / 6.0, start_h - qh / 16.0 - 40);

			snprintf(text, 300, "Type:");
			printToScreen(text, start_w, start_h - qh / 16.0 - 60);

			snprintf(text, 300, "%s", (r.queues.at(i + j).type == FIFO) ? "FIFO" : "LIFO");
			printToScreen(text, start_w + winWidth / 6.0, start_h - qh / 16.0 - 60);

			start_w += winWidth / 3;
		}
		start_h -= qh / 3;
	}
}

/* draw the next event list */
void _draw_next_event_list(System_Information *info)
{
	float lh = next_events.ymax - next_events.ymin;
	char text[300];
	Record r = info->records.at(sim_pos);
	float col1, col2, col3;
	col1 = next_events.xmin;
	col2 = next_events.xmin + (next_events.xmax - next_events.xmin) / 3.0;
	col3 = next_events.xmin + (next_events.xmax - next_events.xmin) / 1.5;

	snprintf(text, 300, "Next Events List");
	printToScreen(text, next_events.xmin, next_events.ymax + 2.0);
	
	glColor3f(0.0, 0.0, 0.0);
	snprintf(text, 300, "Type");
	printToScreen(text, col1, next_events.ymax - lh / 8.0);

	snprintf(text, 300, "Entity");
	printToScreen(text, col2, next_events.ymax - lh / 8.0);

	snprintf(text, 300, "Time");
	printToScreen(text, col3, next_events.ymax - lh / 8.0);

	snprintf(text, 300, "A");
	printToScreen(text, col1, next_events.ymax - lh / 8.0 - 25.0);

	snprintf(text, 300, "%d", r.next_list.at(ARRIVAL).entity);
	printToScreen(text, col2, next_events.ymax - lh / 8.0 - 25.0);

	snprintf(text, 300, "%.1f", r.next_list.at(ARRIVAL).time);
	printToScreen(text, col3, next_events.ymax - lh / 8.0 - 25.0);

	snprintf(text, 300, "D");
	printToScreen(text, col1, next_events.ymax - lh / 8.0 - 50.0);

	snprintf(text, 300, "%d", r.next_list.at(DEPARTURE).entity);
	printToScreen(text, col2, next_events.ymax - lh / 8.0 - 50.0);

	snprintf(text, 300, "%.1f", r.next_list.at(DEPARTURE).time);
	printToScreen(text, col3, next_events.ymax - lh / 8.0 - 50.0);
	
	snprintf(text, 300, "T");
	printToScreen(text, col1, next_events.ymax - lh / 8.0 - 75.0);

	snprintf(text, 300, "%d", r.next_list.at(TERMINATE).entity);
	printToScreen(text, col2, next_events.ymax - lh / 8.0 - 75.0);

	snprintf(text, 300, "%.1f", r.next_list.at(TERMINATE).time);
	printToScreen(text, col3, next_events.ymax - lh / 8.0 - 75.0);
}


/* draw all of the events */
void _draw_event_info(System_Information *info)
{
	float lh = event_info.ymax - event_info.ymin;
	char text[300];
	Event e = info->handler.events.at(sim_pos);

	float col1 = event_info.xmin;
	float col2 = event_info.xmin + (event_info.xmax - event_info.xmin) / 2.0;

	glColor3f(1.0, 1.0, 1.0);
	snprintf(text, 300, "Event Information");
	printToScreen(text, col1, event_info.ymax + 2.0);

	glColor3f(0.0, 0.0, 0.0); 	/* black text */
	snprintf(text, 300, "ID:");
	printToScreen(text, col1, event_info.ymax - lh / 8.0 - 5.0);

	snprintf(text, 300, "%d", e.id);
	printToScreen(text, col2, event_info.ymax - lh / 8.0 - 5.0);

	snprintf(text, 300, "Entity:");
	printToScreen(text, col1, event_info.ymax - lh / 8.0 - 30.0);

	snprintf(text, 300, "%d", e.entity);
	printToScreen(text, col2, event_info.ymax - lh / 8.0 - 30.0);

	snprintf(text, 300, "Time:");
	printToScreen(text, col1, event_info.ymax - lh / 8.0 - 55.0);

	snprintf(text, 300, "%.1f", e.time);
	printToScreen(text, col2, event_info.ymax - lh / 8.0 - 55.0);

	snprintf(text, 300, "Type:");
	printToScreen(text, col1, event_info.ymax - lh / 8.0 - 80.0);

	snprintf(text, 300, "%s", (e.type == ARRIVAL) ? "A" : (e.type == DEPARTURE) ? "D" : "T");
	printToScreen(text, col2, event_info.ymax - lh / 8.0 - 80.0);
}


/* Draw all of the event information */
void _draw_all_events(System_Information *info, int curr_start, int npp)
{
	char text[300];
	EventHandler eh = info->handler;
	int len;
	int end = ((npp + curr_start) >(int)eh.events.size()) ?
		(int)eh.events.size() : npp;

	float pos = winHeight * 0.85 - 40.0;
	glColor3f(1.0, 0.0, 0.0); //red
	
	snprintf(text, 300, "ID");
	len = (int)strlen(text);
	glRasterPos2f(winWidth * 0.20, pos);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

	snprintf(text, 300, "Entity");
	len = (int)strlen(text);
	glRasterPos2f(winWidth * 0.30, pos);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

	snprintf(text, 300, "Time");
	len = (int)strlen(text);
	glRasterPos2f(winWidth * 0.40, pos);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

	snprintf(text, 300, "Type");
	len = (int)strlen(text);
	glRasterPos2f(winWidth * 0.50, pos);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

	glColor3f(1.0, 1.0, 1.0); // white text
	for (int i = 0; i < end; i++)
	{
		Event e = eh.events.at(i + curr_start);
		pos -= 25.0; // adjust position

		snprintf(text, 300, "%d", e.id);
		len = (int)strlen(text);
		glRasterPos2f(winWidth * 0.20, pos);
		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

		snprintf(text, 300, "%d", e.entity);
		len = (int)strlen(text);
		glRasterPos2f(winWidth * 0.30, pos);
		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

		snprintf(text, 300, "%.2f", e.time);
		len = (int)strlen(text);
		glRasterPos2f(winWidth * 0.40, pos);
		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

		snprintf(text, 300, "%s",
			(e.type == ARRIVAL) ? "ARRIVAL" :
			(e.type == DEPARTURE) ? "DEPARTURE" : "TERMINATE");
		len = (int)strlen(text);
		glRasterPos2f(winWidth * 0.50, pos);
		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

	}

}

/* draw all of the statistical information */
void _draw_statisical_info(System_Information &info)
{
	char text[300];
	float pos = winHeight * 0.65;
	glColor3f(1.0, 1.0, 1.0); //white

	snprintf(text, 300, "Total Queues: ");
	int len = (int)strlen(text);
	glRasterPos2f(winWidth * 0.20, pos);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

	snprintf(text, 300, "%d", info.num_queues);
	len = (int)strlen(text);
	glRasterPos2f(winWidth * 0.60, pos);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

	pos -= 20.0;

	snprintf(text, 300, "Total Servers: ");
	len = (int)strlen(text);
	glRasterPos2f(winWidth * 0.20, pos);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

	snprintf(text, 300, "%d", info.num_servers);
	len = (int)strlen(text);
	glRasterPos2f(winWidth * 0.60, pos);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

	pos -= 20.0;

	snprintf(text, 300, "Max Queue Length: ");
	len = (int)strlen(text);
	glRasterPos2f(winWidth * 0.20, pos);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

	snprintf(text, 300, "%d", info.stats.max_num_in_q);
	len = (int)strlen(text);
	glRasterPos2f(winWidth * 0.60, pos);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

	pos -= 20.0;

	snprintf(text, 300, "Max Server Length: ");
	len = (int)strlen(text);
	glRasterPos2f(winWidth * 0.20, pos);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

	snprintf(text, 300, "%d", info.stats.max_num_in_s);
	len = (int)strlen(text);
	glRasterPos2f(winWidth * 0.60, pos);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

	pos -= 20.0;

	snprintf(text, 300, "Left in Queues: ");
	len = (int)strlen(text);
	glRasterPos2f(winWidth * 0.20, pos);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

	snprintf(text, 300, "%d", info.stats.left_in_q);
	len = (int)strlen(text);
	glRasterPos2f(winWidth * 0.60, pos);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

	pos -= 20.0;

	snprintf(text, 300, "Left in Servers: ");
	len = (int)strlen(text);
	glRasterPos2f(winWidth * 0.20, pos);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

	snprintf(text, 300, "%d", info.stats.left_in_s);
	len = (int)strlen(text);
	glRasterPos2f(winWidth * 0.60, pos);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

	pos -= 20.0;

	snprintf(text, 300, "Total Idle Time: ");
	len = (int)strlen(text);
	glRasterPos2f(winWidth * 0.20, pos);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

	snprintf(text, 300, "%.3f", info.stats.idle_time_s);
	len = (int)strlen(text);
	glRasterPos2f(winWidth * 0.60, pos);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

	pos -= 20.0;

	snprintf(text, 300, "Server Utilization: ");
	len = (int)strlen(text);
	glRasterPos2f(winWidth * 0.20, pos);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

	snprintf(text, 300, "%.3f", info.stats.percent_util);
	len = (int)strlen(text);
	glRasterPos2f(winWidth * 0.60, pos);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

	pos -= 20.0;

	snprintf(text, 300, "Average Interarrival Time: ");
	len = (int)strlen(text);
	glRasterPos2f(winWidth * 0.20, pos);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);

	snprintf(text, 300, "%.3f", info.stats.avg_inter_arrivals);
	len = (int)strlen(text);
	glRasterPos2f(winWidth * 0.60, pos);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
}

/* Draw the initial home screen menu */
void _draw_initial() 
{
	_draw_button(start);
	if( sim_pos > 0 ) _draw_button(cont);

}

/* Draw the queues and their information */
void _draw_queues()
{

	if( curr_start > 0 )
		_draw_arrow(up);
	if( curr_start < info.num_queues - 9)
		_draw_arrow(down);

	_draw_all_queues(&info, curr_start);
	_draw_button(back);
}

/* Draw the servers and their information */
void _draw_servers() 
{

	if (curr_start > 0)
		_draw_arrow(up);
	if (curr_start < info.num_servers - 9)
		_draw_arrow(down);

	_draw_all_servers(&info, curr_start);
	_draw_button(back);
}

/*
* Draw the all of the events in the order in which
* they will occur. Include event information to ensure
* the viewer is well informed.
*/
void _draw_all_events()
{
	float h = winHeight * 0.85 - 60.0;
	int npp = h / 25; // num per page

	if (curr_start > 0)
		_draw_arrow(up);
	
	if((curr_start + npp) < (int)info.handler.events.size())
		_draw_arrow(down);

	_draw_all_events(&info, curr_start, npp);

	_draw_button(back);
}


/*
* Draw the statistical information from the start of
* the simulation until the current point.
*/
void _draw_stats() 
{
	_draw_button(generate_report);
	_draw_button(back);
	_draw_statisical_info(info);
}


/* Draw the home screen or the starting screen for the simulation */
void _draw_home() 
{
	_draw_button(home); 
	_draw_button(event_info);
	// draw current event information
	_draw_event_info(&info);

	_draw_button(next_events);
	// Draw the next event information
	_draw_next_event_list(&info);

	_draw_button(all_events);
	_draw_button(queues);
	_draw_button(servers);
	 

	if( sim_pos > 0 )
		_draw_button(prev);
	if (sim_pos < getTermination(&info))
		_draw_button(next);
	else
		_draw_button(stats);

}

/*********************** END PRIVATE INTERNAL FUNCTIONS **********************/

/* public draw for internal function calls */
void draw_display(int state) 
{	
	_draw_button(quit);	/* always draw quit */

	switch (state) {
	case INITIAL:       _draw_initial();    break;
	case HOME:          _draw_home();       break;
	case ALL_EVENTS:    _draw_all_events(); break;
	case QUEUES:        _draw_queues();     break;
	case SERVERS:       _draw_servers();    break;
	case STATS:         _draw_stats();      break;
	}
}
