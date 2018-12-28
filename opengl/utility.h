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

int minQueue(System_Information *info);
int minServer(System_Information *info);
bool removeEvent(System_Information *info, Event e);
int compareType(ETYPE E, ETYPE F, int *event_order);
void orderEvents(System_Information *info);
void createRecords(System_Information *info);
int findEvent(EventHandler eh, Event e);
bool nextEvent(EventHandler *eh, Event &e, ETYPE type, int id = -1);
void getNextEventList(Record *r, EventHandler *eh);
int getTermination(System_Information * info);
void auto_color(button &btn, int x, int y, float r, float g, float b);
void auto_color(arrow &a, int x, int y, float r, float g, float b);
void change_color(color &c, float r, float g, float b);
void check_mouse_pos(int x, int y);
void select(int x, int y);
void printToScreen(char text[300], float x, float y);

#endif