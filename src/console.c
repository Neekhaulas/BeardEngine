#include "common.h"
#ifdef WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>

char* command_input;

#ifndef WIN32
pollfd cinfd[1];
#else
HANDLE h;
#endif

char * getline(void) {
	char * line = malloc(100), *linep = line;
	size_t lenmax = 100, len = lenmax;
	int c;

	if (line == NULL)
		return NULL;

	for (;;) {
		c = fgetc(stdin);
		if (c == EOF)
			break;

		if (--len == 0) {
			len = lenmax;
			char * linen = realloc(linep, lenmax *= 2);

			if (linen == NULL) {
				free(linep);
				return NULL;
			}
			line = linen + (line - linep);
			linep = linen;
		}

		if ((*line++ = c) == '\n')
			break;
	}
	*--line = '\0';
	return linep;
}

void Console_Init()
{
#ifndef WIN32
	// Theoretically this should always be 0, but one fileno call isn't going to hurt, and if
	// we try to run somewhere that stdin isn't fd 0 then it will still just work
	cinfd[0].fd = fileno(stdin);
	cinfd[0].events = POLLIN;
#else
	h = GetStdHandle(STD_INPUT_HANDLE);
#endif
}

void Console_Frame()
{
#ifndef WIN32
	if (poll(cinfd, 1, 1000))
#else
	if (WaitForSingleObject(h, 0) == WAIT_OBJECT_0)
#endif
	{
		command_input = getline();
		Command_Exec(command_input);
	}
}

void Console_Print(char* msg)
{
#ifdef DEDICATED
	fprintf(stdout, "%s\n", msg);
#else
	fprintf(stdout, "%s\n", msg);
#endif
}