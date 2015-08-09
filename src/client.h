
#ifndef __CLIENT_H
#define __CLIENT_H

#include "shared.h"

typedef struct
{
	snapshot *snap;
	snapshot *nextSnap;

	int time;
	int frame;
	int physicTime;
} game;

void Client_Init();
void Client_Process_Events();

#endif