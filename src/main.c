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

#define DEDICATED

#ifndef DEDICATED
#include <SDL.h>
#endif

#include "shared.h"
#include "common.h"

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
  Cvar_Init();
  Cvar_Set("g_developper", "1", CVAR_READ_ONLY, "If the developper mod is on");
  Cvar_Set("net_master_server", "be.grandebar.be", CVAR_READ_ONLY, "Address of the master server");
  Cvar_Set("width_screen", "1400", CVAR_USER_CREATED, NULL);
  Cvar_Set("height_screen", "900", CVAR_USER_CREATED, NULL);
  Cvar_Print("g_developper");
  Cvar_Print("net_master_server");
  Cvar_Print("hello_world");
  Cvar_Print("width_screen");
  Cvar_Print("height_screen");

  Cvar_Set("g_developper", "0", 0, NULL);
  Cvar_Print("g_developper");

  while (1)
  {

  }
  return 0;
}
