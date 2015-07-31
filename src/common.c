#include "common.h"

#include <stdarg.h>

void Print(char* format, ...)
{
	char print[1024];
	va_list arglist;

	va_start(arglist, format);

	vsprintf(print, format, arglist);

	va_end(arglist);

	ConsolePrint(print);
}