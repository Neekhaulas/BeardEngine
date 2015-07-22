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

//#define DEDICATED

#ifndef DEDICATED
#include <SDL.h>
#endif

#include "shared.h"
#include "common.h"

void ParseArgs( int argc, char **argv )
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
  return 0;
}
