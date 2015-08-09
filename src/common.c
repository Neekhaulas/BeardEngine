#include "common.h"

#ifndef DEDICATED
#include "client.h"
#endif

#include <stdarg.h>
#include <physfs.h>

Cvar* dedicated;
Cvar* version;
Cvar* developper;

Cvar* s_masterserver;

Cvar* g_gravity;

void Print(char* format, ...)
{
	char print[1024];
	va_list arglist;

	va_start(arglist, format);

	vsprintf(print, format, arglist);

	va_end(arglist);

	Console_Print(print);
}

char* CopyString(const char* str)
{
	char* cpy;
	cpy = malloc(strlen(str)+1);

	strcpy(cpy, str);

	return cpy;
}

void Quit()
{
	Shutdown();
}

void Shutdown()
{
#ifndef DEDICATED
	SDL_Quit();
#endif
	exit(0);
}

void Init(char* command)
{
	Cvar_Init();
	PHYSFS_init(NULL);

	Command_Init();

	//Init Cvar

	const char* date = __DATE__;
	char* version_str = malloc(strlen(PRODUCT_NAME " client " VERSION " (%s)")+1);
#ifdef DEDICATED
	dedicated = Cvar_Set("dedicated", "1", CVAR_READ_ONLY, "If this is dedicated server");
	sprintf(version_str, PRODUCT_NAME " dedicated server " VERSION " (%s)", date);
	version = Cvar_Set("version", version_str, CVAR_READ_ONLY, "Version of the client");
#else
	dedicated = Cvar_Set("dedicated", "0", CVAR_READ_ONLY, "If this is dedicated server");
	sprintf(version_str, PRODUCT_NAME " client " VERSION " (%s)", date);
	version = Cvar_Set("version", version_str, CVAR_READ_ONLY, "Version of the client");
#endif
	developper = Cvar_Set("developer", "1", CVAR_READ_ONLY, "If the developper mod is on");

	s_masterserver = Cvar_Set("s_masterserver", MASTERSERVER, CVAR_READ_ONLY, "Address of the master server");

	g_gravity = Cvar_Set("g_gravity", "800", CVAR_CHEATS, "Gravity of the game");

#ifndef DEDICATED
	Client_Init();
	Console_Init();
#else
	Console_Init();
#endif

	Command_Add("quit", Quit);
}

void Game_Frame()
{

}