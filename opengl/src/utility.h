#ifndef _UTILITY_H
#define _UTILITY_H

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <vector>
#include "Common.h"
#include <limits>
#include "printStructs.h"
#include "geometry.h"
#include "states.h"
#include "readWriteFile.h"

//int minQueue(System_Information *info);
//int minServer(System_Information *info);
bool removeEvent(System_Information *info, Event e);
//int compareType(ETYPE E, ETYPE F, int *event_order);
//void orderEvents(System_Information *info);
void createRecords(System_Information *info);
int findEvent(EventHandler eh, Event e);
bool nextEvent(EventHandler *eh, Event &e, ETYPE type, int id = -1);
void getNextEventList(Record *r, EventHandler *eh);
int getTermination(System_Information * info);

#endif