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

void Clamp(float& value, float min, float max)
{
	value = value < min ? min : (value > max ? max : value);
}

#ifndef SERVER

void Shutdown()
{
	SDL_Quit();
	Client_Cleanup();
	exit(0);
}

int Init(char* command)
{
	Cvar_Init();

	Command_Init();

	Command_Add("quit", Shutdown);

	//Init Cvar

	Cvar_Set("developer", "1", CVAR_READ_ONLY, "If the developper mod is on");
	Cvar_Set("s_masterserver", MASTERSERVER, CVAR_READ_ONLY, "Address of the master server");
	Cvar_Set("g_gravity", "4", CVAR_CHEATS, "Gravity of the game");

	char* date = __DATE__;
	char version_str[256];

	Cvar_Set("dedicated", "0", CVAR_READ_ONLY, "If this is dedicated server");
	sprintf(version_str, PRODUCT_NAME " client 1 (%s)", date);
	Cvar_Set("version", version_str, CVAR_READ_ONLY, "Version of the client");
	Cvar_Set("width_screen", "1024", CVAR_USER_CREATED, NULL);
	Cvar_Set("height_screen", "768", CVAR_USER_CREATED, NULL);

	Command_Exec("exec var.cfg");
	
	Game_Init();

	Render_Init();

	Client_Init();

	Command_Exec("exec bind.cfg");

	return 0;
}

#endif