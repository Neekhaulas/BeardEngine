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

#ifndef DEDICATED
#include <SDL.h>
#else
#include "server.h"
#ifdef WIN32
#include <windows.h>
#endif
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

int main (int argc, char **argv)
{
	ParseArgs( argc, argv );
	Init(NULL);
	Cvar_Set("s_masterserver", "be.grandebar.be", CVAR_READ_ONLY, "Address of the master server");
	Cvar_Set("width_screen", "1400", CVAR_USER_CREATED, NULL);
	Cvar_Set("height_screen", "900", CVAR_USER_CREATED, NULL);

	Cvar_Set("width_screen", "800", CVAR_USER_CREATED, NULL);
	Cvar_Reset("width_screen");

	while (1)
	{
#ifndef DEDICATED
		Input_Frame();
		//Console_Frame();
#else
		Console_Frame();
#endif
		Game_Frame();
	}

	return 0;
}
