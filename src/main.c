#include <signal.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <stdarg.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "shared.h"
#include "common.h"

#include <SDL.h>
#ifdef WIN32
#include <windows.h>
#endif


void ParseArgs(int argc, char **argv)
{
  if( argc == 2 )
  {
    if ( !strcmp( argv[1], "--version" ) || !strcmp( argv[1], "-v" ) )
    {
      const char* date = __DATE__;
      #ifdef DEDICATED
      fprintf(stdout, PRODUCT_NAME " dedicated server " VERSION " (%s)\n", date);
      #else
      fprintf(stdout, PRODUCT_NAME " client " VERSION " (%s)\n", date);
      #endif
    }
    exit(0);
  }
}

void handle_input()
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_KEYDOWN:
			Event_Queue(EVENT_KEY, e.key.keysym.sym, 1);
			
			break;

		case SDL_KEYUP:
			Event_Queue(EVENT_KEY, e.key.keysym.sym, 0);
			break;

		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			int b;
			switch (e.button.button)
			{
			case SDL_BUTTON_LEFT: b = KEY_MOUSE1; break;
			case SDL_BUTTON_MIDDLE: b = KEY_MOUSE2; break;
			case SDL_BUTTON_RIGHT: b = KEY_MOUSE3; break;
			}
			Event_Queue(EVENT_KEY, b, (e.type == SDL_MOUSEBUTTONDOWN) ? 1 : 0);
			break;

		case SDL_MOUSEMOTION:
			Game_Mouse_Move(e.motion.x, e.motion.y);
			break;

		case SDL_MOUSEWHEEL:
			Print("mouse wheel : %d", e.wheel.y);
			Game_Mouse_Wheel(e.wheel.y);
			break;

		case SDL_QUIT:
			Command_Exec("quit");
			break;
		}
	}
}

int lastTime = 0;

int main (int argc, char **argv)
{
	ParseArgs( argc, argv );
	if (Init(NULL) != 0)
		return 1;

	for (;;)
	{
		handle_input();
		Event_Loop();
		int time = SDL_GetTicks();
		Game_Update_World(time, lastTime);
		Render_Draw_Frame();
		lastTime = time;
	}

	return 0;
}
