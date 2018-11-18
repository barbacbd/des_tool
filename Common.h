#ifndef _COMMON_H
#define _COMMON_H

#pragma once
#include <vector>

#define _DEBUG_PRG
#define FULLSCREEN_MODE

/* 
* time value can be either float or int 
*/
typedef float prec;

/* 
* Enumeration for the Type of event that has
* been activated in the system. 
*/
enum ETYPE
{
	ARRIVAL,
	DEPARTURE,
	TERMINATE
};

/*
* Enumeration for the Type of queue(s) that the user
* wants the system to contain. Either First-in-First-out
* or Last-in-First-Out.
*/
enum QTYPE
{
	FIFO,
	LIFO
};

/* 
* The structure containing all information necessary to
* be an event. The information will be processed throughout
* the simulation. This structure will contain the main
* information entered by the user into the text file(s).
*/
struct Event
{
	int id;
	int entity;
	ETYPE type;
	prec time;
	bool occurred;
};

/*
* The Queue struct will hold information entered by the user,
* and it will contain a list of all Events that are waiting 
* to proceed to the server.
*/
struct Queue
{
	int capacity;
	int total;
	QTYPE type;
	std::vector<struct Event> events;
};

/*
* The Server struct will hold information entered by the user,
* and it will contain a [list] of all events that are being
* served. 
*/
struct Server
{
	int capacity;
	int total;
	std::vector<struct Event> events;
};

/*
* The EventHandler struct will dictate the flow of the
* simulation. All Events will be created and added to the
* struct, then the struct will pass the events onto the
* Queue when it is time for the next event to occur.
*/
struct EventHandler
{
	std::vector<struct Event> events;
};

/*
* The Record struct will serve as a snapshot of the
* system at the time -> time
*/
struct Record
{
	int id; 
	prec time;
	std::vector<struct Event> next_list;
	std::vector<struct Queue> queues;
	std::vector<struct Server> servers;
};

/*
* Common structure to hold statistical information
*/
struct statistics
{
	std::vector<prec> inter_arrivals;
	float avg_inter_arrivals;

	int max_num_in_q;
	int max_num_in_s;

	int left_in_q;
	int left_in_s;
	prec idle_time_s;
	float percent_util; // percentage of time utilization by servers
};

/* 
* Struct to hold all information about the system
*/
struct System_Information
{
	int num_queues;
	int num_servers;
	int queue_cap;
	int server_cap;
	QTYPE q_type;
	//std::vector<int> event_order;
	int *event_order;

	struct EventHandler handler;
	/*
	* Deciding on the necessity for queues and servers in this struct
	*/
	std::vector<struct Queue> queues;
	std::vector<struct Server> servers;

	std::vector<struct Record> records;

	statistics stats;
};

/* Simple color structure - used to control and 
* alter the color of buttons */
struct color
{
	float r;
	float g;
	float b;
};

/*
* Common structure to create all of the buttons for the display
*/
struct button
{
	float xmin;
	float xmax;
	float ymin;
	float ymax;
	char *text;
	color c;
};



/*
* Common structure to draw an up or down arrow
*/
struct arrow
{
	button b;
	int dir; /* 0 - up, 1 - down */
};


/* variables for the display */
extern int winHeight, winWidth;
extern System_Information info;
extern int state, sim_pos;
extern int curr_start;
extern std::vector<std::string> filenames;

/* colors of the representative buttons */
extern button home;
extern button quit;
extern button all_events;
extern button event_info;
extern button queues;
extern button servers;
extern button next_events;
extern button stats;
extern button next;
extern button prev;
extern button back;
extern button start;
extern button cont;
extern button generate_report;
extern arrow up;
extern arrow down;

#endif