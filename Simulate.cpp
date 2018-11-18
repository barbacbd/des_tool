#include "stdafx.h"
#include "Simulate.h"

/* Create the manual simulation of all events */
void simulateDES(System_Information *info)
{
	/* Create the list of queues */
	for (int i = 0; i < info->num_queues; i++) 
	{
		struct Queue q;
		q.capacity = info->queue_cap;
		q.total = 0;
		q.type = info->q_type;
		info->queues.push_back(q);
	}

	/* create the list of servers */
	for (int i = 0; i < info->num_servers; i++)
	{
		struct Server s;
		s.capacity = info->server_cap;
		s.total = 0;
		info->servers.push_back(s);
	}

	orderEvents( info );
	createRecords( info );
	create_statistics( info );
}

