#include "stdafx.h"
#include "button.h"


/* button setup information */
void button_setup() 
{
	//
	// IMPORTANT -- COORDINATES are backwards in y dir
	//

	button_pos_setup(up.b, "", winWidth * 0.35, winWidth * 0.45,
		winHeight * 0.85, winHeight * 0.95);
	up.dir = 0; // up direction

	button_pos_setup(down.b, "", winWidth * 0.55, winWidth * 0.65,
		winHeight * 0.85, winHeight * 0.95);
	down.dir = 1; // down direction

	button_pos_setup(start, "Start", winWidth * 0.40, winWidth * 0.60,
		winHeight * 0.60, winHeight * 0.70);

	button_pos_setup(cont, "Continue", winWidth * 0.40, winWidth * 0.60,
		winHeight * 0.40, winHeight * 0.50);

	button_pos_setup(quit, "Quit", winWidth * 0.85, winWidth * 0.95,
		winHeight * 0.85, winHeight * 0.95);

	button_pos_setup(home, "Home", winWidth * 0.05, winWidth * 0.15,
		winHeight * 0.85, winHeight * 0.95);

	button_pos_setup(back, "Back", winWidth * 0.05, winWidth * 0.15,
		winHeight * 0.85, winHeight * 0.95);

	button_pos_setup(event_info, "", winWidth * 0.05,
		winWidth * 0.25, winHeight * 0.55, winHeight * 0.75);

	button_pos_setup(next_events, "", winWidth * 0.75,
		winWidth * 0.95, winHeight * 0.55, winHeight * 0.75);

	button_pos_setup(all_events, "All-Events", winWidth * 0.45, winWidth * 0.55,
		winHeight * 0.60, winHeight * 0.70);

	button_pos_setup(queues, "Queues", winWidth * 0.25, winWidth * 0.35,
		winHeight * 0.35, winHeight * 0.45);

	button_pos_setup(stats, "Statistics", winWidth * 0.45, winWidth * 0.55,
		winHeight * 0.05, winHeight * 0.15);

	button_pos_setup(servers, "Servers", winWidth * 0.65,
		winWidth * 0.75, winHeight * 0.35, winHeight * 0.45);

	button_pos_setup(prev, "Previous", winWidth * 0.05, winWidth * 0.15,
		winHeight * 0.05, winHeight * 0.15);

	button_pos_setup(next, "Next", winWidth * 0.85, winWidth * 0.95,
		winHeight * 0.05, winHeight * 0.15);

	button_pos_setup(generate_report, "Generate-Report", winWidth * 0.45, 
		winWidth * 0.55, winHeight * 0.85, winHeight * 0.95);
}

/* button position setup */
void button_pos_setup(button &b, char * text, float xmin,
	float xmax, float ymin, float ymax) 
{
	b.xmin = xmin;
	b.xmax = xmax;
	b.ymin = ymin;
	b.ymax = ymax;
	b.text = text;
}

/* set all of the colors of the buttons to white */
void set_colors() 
{
	home.c.r = home.c.g = home.c.b = 1.0;
	quit.c.r = quit.c.g = quit.c.b = 1.0;
	all_events.c.r = all_events.c.g = all_events.c.b = 1.0;
	event_info.c.r = event_info.c.g = event_info.c.b = 1.0;
	queues.c.r = queues.c.g = queues.c.b = 1.0;
	servers.c.r = servers.c.g = servers.c.b = 1.0;
	next_events.c.r = next_events.c.g = next_events.c.b = 1.0;
	stats.c.r = stats.c.g = stats.c.b = 1.0;
	next.c.r = next.c.g = next.c.b = 1.0;
	prev.c.r = prev.c.g = prev.c.b = 1.0;
	back.c.r = back.c.g = back.c.b = 1.0;
	start.c.r = start.c.g = start.c.b = 1.0;
	cont.c.r = cont.c.g = cont.c.b = 1.0;
	up.b.c.r = up.b.c.g = up.b.c.b = 1.0;
	down.b.c.r = down.b.c.g = down.b.c.b = 1.0;
	generate_report.c.r = generate_report.c.g = generate_report.c.b = 1.0;
}
