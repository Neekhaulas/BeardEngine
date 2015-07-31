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

char* CopyString(char* str)
{
	char* cpy;
	cpy = malloc(strlen(str)+1);

	strcpy(cpy, str);

	return cpy;
}