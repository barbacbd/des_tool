#include "statistics.h"

/********************** Private statistical functions ************************/

/* get the number left in the servers */
void _num_left_in_servers(System_Information *info)
{
	info->stats.left_in_s = 0;
	for (int i = 0; i < info->num_servers; i++)
		info->stats.left_in_s += 
			info->records.at(getTermination(info)).servers.at(i).total;
}

/* get the number left in the queues */
void _num_left_in_queues(System_Information *info)
{
	info->stats.left_in_q = 0;
	for (int i = 0; i < info->num_queues; i++)
		info->stats.left_in_q += 
			info->records.at(getTermination(info)).queues.at(i).total;
}

/* get the maximum amount in a queue */
void _get_max_queue(System_Information *info)
{
	int max_queue = -1;
	for (int i = 0; i < (int)info->records.size(); i++)
	{
		for (int j = 0; j < info->num_queues; j++)
		{
			if (info->records.at(i).queues.at(j).total > max_queue)
				max_queue = info->records.at(i).queues.at(j).total;
		}
	}
	info->stats.max_num_in_q = max_queue;
}

/* get the maximum amount in a server */
void _get_max_server(System_Information *info)
{
	int max_server = -1;
	for (int i = 0; i < (int)info->records.size(); i++)
	{
		for (int j = 0; j < info->num_servers; j++)
		{
			if (info->records.at(i).servers.at(j).total > max_server)
				max_server = info->records.at(i).servers.at(j).total;
		}
	}
	info->stats.max_num_in_s = max_server;
}

/* find the idle time of the servers */
void _find_idle_time(System_Information *info)
{
	prec last_time = 0;

	info->stats.idle_time_s = 0;
	for (int i = 0; i < (int)info->records.size(); i++)
	{
		for (int j = 0; j < info->num_servers; j++)
		{
			if (info->records.at(i).servers.at(j).total == 0)
			{
				info->stats.idle_time_s += (info->records.at(i).time-last_time);
			}
		}
		last_time = info->records.at(i).time;
	}
}

/* find the percent utilization of the servers */
void _get_percent_util(System_Information *info)
{
	int total = 0;
	int terminate = getTermination(info) + 1;
	for (int i = 0; i < terminate; i++)
	{
		for (int j = 0; j < info->num_servers; j++)
		{
			total += info->records.at(i).servers.at(j).total;
		}
	}
	info->stats.percent_util = (float)total / (float)(terminate *
		info->num_servers * info->server_cap);
}

/* determine all of the interarrival times for the events */
void _calc_interarrivals(System_Information *info)
{
	prec time = 0;
	Event e;

	for (int i = 0; i < getTermination(info); i++)
	{
		if (info->handler.events.at(i).type == ARRIVAL)
		{
			info->stats.inter_arrivals.push_back(
				info->handler.events.at(i).time - time);

			// set the time to the time of last arrival
			time = info->handler.events.at(i).time;
		}
	}
}

/* calculate the average of all of the interarrival times */
void _avg_interarrivals(System_Information *info)
{
	//
	// IMPORTANT - run after calculating the interarrivals
	//

	for (int i = 0; i < (int)info->stats.inter_arrivals.size(); i++)
	{
		info->stats.avg_inter_arrivals += 
			(float)info->stats.inter_arrivals.at(i);
	}
	info->stats.avg_inter_arrivals /= (float)info->stats.inter_arrivals.size();
}

/*****************************************************************************/

//
///*
//	calculate ...
//
//	1. Amount left in Servers
//	2. Amount left in Queues
//	3. Idle Time of Servers
//	4. Percent Utilization of Servers
//	5. Max num in Queues
//	6. Max num in servers
//	7. Average Interarrival Times
//*/
//void create_statistics(System_Information *info)
//{
//	_num_left_in_servers(info);
//	_num_left_in_queues(info);
//	_find_idle_time(info);
//	_get_percent_util(info);
//	_get_max_queue(info);
//	_get_max_server(info);
//	_calc_interarrivals(info);
//	_avg_interarrivals(info);
//}
