#ifndef _PRINT_STRUCTS_H
#define _PRINT_STRUCTS_H
#pragma once
#include "Common.h"

void printEventType(ETYPE e);
void printQueueType(QTYPE q);
void printEvent(Event *e);
void printQueue(Queue *q);
void printServer(Server *s);
void printEventHandler(EventHandler *eh);
void printRecord(Record *r);
void printSystemInformation(System_Information *si);

#endif