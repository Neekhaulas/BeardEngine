#include "client.h"
#include "client_input.h"

#ifndef DEDICATED

static SDL_Window *window = NULL;

void Client_Init()
{
	Print("Window initializing");
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		Print("Can't initialize SDL Video");
		exit(1);
	}

	window = SDL_CreateWindow(CLIENT_WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	if (!window)
	{
		Print("Can't create SDL window");
		exit(1);
	}

	Client_Init_Input();
}

void Input_Frame()
{
	Client_Process_Events();
}

#endif