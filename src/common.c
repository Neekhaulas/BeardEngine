#include "common.h"

#ifndef SERVER
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
	if (level > ERROR_LEVEL)
		return;
	char print[1024];
	va_list arglist;

	va_start(arglist, format);

	vsprintf(print, format, arglist);

	va_end(arglist);

	Console_Print(print);
}

char* CopyString(const char* str)
{
	if (!str)
		return NULL;
	char *cpy;
	cpy = (char*)malloc(strlen(str)+1);

	strcpy(cpy, str);

	return (char*)cpy;
}

#ifndef SERVER

Cvar* dedicated;
Cvar* version;
Cvar* developper;
Cvar* s_masterserver;
Cvar* g_gravity;

void Shutdown()
{
	SDL_Quit();
	Client_Cleanup();
	exit(0);
}

int Init(char* command)
{
	Render_Init();

	Cvar_Init();

	Command_Init();

	Command_Add("quit", Shutdown);

	//Init Cvar

	developper = Cvar_Set("developer", "1", CVAR_READ_ONLY, "If the developper mod is on");
	s_masterserver = Cvar_Set("s_masterserver", MASTERSERVER, CVAR_READ_ONLY, "Address of the master server");
	g_gravity = Cvar_Set("g_gravity", "800", CVAR_CHEATS, "Gravity of the game");

	char* date = __DATE__;
	char version_str[256];

	dedicated = Cvar_Set("dedicated", "0", CVAR_READ_ONLY, "If this is dedicated server");
	sprintf(version_str, PRODUCT_NAME " client " VERSION " (%s)", date);
	version = Cvar_Set("version", version_str, CVAR_READ_ONLY, "Version of the client");

	Client_Init();
	
	Command_Exec("exec autoexec.cfg");

	return 0;
}

#endif