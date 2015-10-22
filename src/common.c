#include "common.h"

#ifndef DEDICATED
#include "client.h"
#endif

#include <stdarg.h>

void Print(char* format, ...)
{
	char print[1024];
	va_list arglist;

	va_start(arglist, format);

	vsprintf(print, format, arglist);

	va_end(arglist);

	Console_Print(print);
}

void Print_Error(int level, char* format, ...)
{
	if (level > error_reporting->value)
		return;
	char print[1024];
	va_list arglist;

	va_start(arglist, format);

	vsprintf(print, format, arglist);

	va_end(arglist);

	Console_Print(print);
}

char* Format(char *format, ...)
{
	char print[1024];
	va_list arglist;

	va_start(arglist, format);

	vsprintf(print, format, arglist);

	va_end(arglist);

	return print;
}

char* CopyString(const char* str)
{
	if (!str)
		return NULL;
	char* cpy;
	cpy = malloc(strlen(str)+1);

	strcpy(cpy, str);

	return cpy;
}

#ifndef SERVER

void Shutdown()
{
	SDL_Quit();
	exit(0);
}

int Init(char* command)
{
	Cvar_Init();

	Command_Init();

	//Init Cvar

	developper = Cvar_Set("developer", "1", CVAR_READ_ONLY, "If the developper mod is on");
	s_masterserver = Cvar_Set("s_masterserver", MASTERSERVER, CVAR_READ_ONLY, "Address of the master server");
	g_gravity = Cvar_Set("g_gravity", "800", CVAR_CHEATS, "Gravity of the game");
	error_reporting = Cvar_Set("error_reporting", "4", CVAR_READ_ONLY, "Level of error");

	char* date = __DATE__;
	char* version_str = malloc(strlen(PRODUCT_NAME " client " VERSION " (%s)") + 1);

	dedicated = Cvar_Set("dedicated", "0", CVAR_READ_ONLY, "If this is dedicated server");
	sprintf(version_str, PRODUCT_NAME " client " VERSION " (%s)", date);
	version = Cvar_Set("version", version_str, CVAR_READ_ONLY, "Version of the client");

	Client_Init();

	Command_Exec("exec autoexec.cfg");

	return 0;
}

void Game_Frame()
{
	Event_Loop();
}

#endif