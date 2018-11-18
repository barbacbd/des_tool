#include "stdafx.h"
#include "readFile.h"

using namespace std;


/* Private function - leave out of the header file */
std::string removeWhitespace(string str) 
{
	str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
	return str;
}

void readFile(string fileName, System_Information *info) 
{
	string line;
	ifstream inFile(fileName.c_str());

	if (!inFile.is_open()) 
	{
		cout << fileName << " couldn't be opened.\n";
		system("pause");
		exit(1);
	}

	/* temporary data storage -- move to global or somewhere else */
	int num_queues, num_servers, queue_cap, server_cap;
	QTYPE q_type;
	//int event_order[3] = {0, 0, 0};

	int col = 0; /* looking for the colon on the line */
	while (getline(inFile, line)) 
	{
		col = line.find_first_of(':');
		if (col > 0) 
		{
			/* this is setup information - NOT the events */
			if ( !line.substr(0, col).compare("Queue Capacity") ) 
			{
				/* Ex: integer number */
				queue_cap = stoi(line.substr(col + 1, 
					(int)line.length() - (col + 1)));
				
				/* error checking */
				if( queue_cap <= 0 )
					queue_cap = numeric_limits<int>::max();
			}
			else if (!line.substr(0, col).compare("Number of Queues"))
			{
				/* Ex: integer number */
				num_queues = stoi(line.substr(col + 1, 
					(int)line.length() - (col + 1)));

				/* error checking */
				if (num_queues <= 0)
					num_queues = 1;
			}
			else if (!line.substr(0, col).compare("Server Capacity"))
			{
				/* Ex: integer number */
				server_cap = stoi(line.substr(col + 1, 
					(int)line.length() - (col + 1)));

				/* error checking */
				if( server_cap <= 0 )
					server_cap = std::numeric_limits<int>::max();
			}
			else if (!line.substr(0, col).compare("Number of Servers"))
			{
				/* Ex: integer number */
				num_servers = stoi(line.substr(col + 1, 
					(int)line.length() - (col + 1)));

				/* error checking */
				if (num_servers <= 0)
					num_servers = 1;
			}
			else if (!line.substr(0, col).compare("Queue Type")) 
			{
				string type = line.substr(col + 1, 
					(int)line.length() - (col + 1));
				type = removeWhitespace(type);

				/* FIFO or LIFO */
				if (!type.compare("FIFO"))
				{
					q_type = FIFO;
				}
				else if (!type.compare("LIFO"))
				{
					q_type = LIFO;
				}
			}
			else if (!line.substr(0, col).compare("Event Order")) 
			{
				string order = line.substr(col + 1, (int)line.length() - (col + 1));
				/* Event Order -> EX: Arrival, Depart, Terminate */
				char *str = _strdup(order.c_str());
				char * token;
				token = strtok(str, ", \t");
				int pos = 0;
				bool arrived = false;
				bool departed = false;
				bool terminated = false;

				while (token) 
				{
					//
					// IMPORTANT - IMPLEMENT a search to ensure the 
					//             Event type is not present already
					//

					if ((!strcmp(token, "Arrival") || !strcmp(token, "A"))
						&& !arrived ) 
					{
						info->event_order[ARRIVAL] = pos;
						pos++; /* update position */
						arrived = true;
					}
					else if ((!strcmp(token, "Departure") || !strcmp(token, "D")) 
						&& !departed ) 
					{
						info->event_order[DEPARTURE] = pos;
						pos++; /* update position */
						departed = true;
					}
					else if ((!strcmp(token, "Terminate") || !strcmp(token, "T")) 
						&& !terminated )
					{
						info->event_order[TERMINATE] = pos;
						pos++; /* update position */
						terminated = true;
					}

					token = strtok(NULL, ", \t");
				}

				free(str); /* memory memory from strdup */
			}

		}
		else 
		{
			/* Event Number - Entity Affected - Event Type - Event Time */
			char *str = _strdup(line.c_str());
			char * token;
			token = strtok(str, " \t");
			
			int e_number, e_affected, e_time, i = 0;
			ETYPE e_type;

			while (token)
			{
				if (i == 0)
				{
					e_number = atoi(token);
				}
				else if (i == 1)
				{
					e_affected = atoi(token);
				}
				else if (i == 2)
				{
					if (!strcmp(token, "Arrive")) 
					{
						e_type = ARRIVAL;
					}
					else if (!strcmp(token, "Depart"))
					{
						e_type = DEPARTURE;
					}
					else if (!strcmp(token, "Terminate"))
					{
						e_affected = -1;
						e_type = TERMINATE;
					}
					else
					{
						printf("Invalid Event Type.\n");
						return;
					}
				}
				else if (i == 3)
				{
					e_time = atoi(token);
				}
				else 
				{
					printf("Too many values provided for an event.\n");
					return;
				}
				token = strtok(NULL, " \t");
				i++;
			}

			/* local scope object */
			struct Event e;
			e.type = e_type;
			e.time = e_time;
			e.id = e_number;
			e.entity = e_affected;
			e.occurred = false;

			/* Add the event to the EventHandler */
			info->handler.events.push_back(e);
		}
	}

	/* set the system information */
	info->num_queues = num_queues;
	info->num_servers = num_servers;
	info->queue_cap = queue_cap;
	info->server_cap = server_cap;
	info->q_type = q_type;
	//info->event_order = event_order;

	inFile.close();
}