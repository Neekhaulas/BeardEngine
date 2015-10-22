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

		case SDL_QUIT:
			Command_Exec("quit");
			break;
		}
	}
}

int main (int argc, char **argv)
{
	ParseArgs( argc, argv );
	if (Init(NULL) != 0)
		return 1;
	Cvar_Set("width_screen", "1400", CVAR_USER_CREATED, NULL);
	Cvar_Set("height_screen", "900", CVAR_USER_CREATED, NULL);

	for (;;)
	{
		handle_input();
		Game_Update_World();
	}

	return 0;
}
