#include "client_input.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

key keys[MAX_KEYS];

keyname_t keynames[] =
{
	{ "F1", SDLK_F1 },
	{ "F2", SDLK_F2 },
	{ "F3", SDLK_F3 },
	{ "F4", SDLK_F4 },
	{ "F5", SDLK_F5 },
	{ "F6", SDLK_F6 },
	{ "F7", SDLK_F7 },
	{ "F8", SDLK_F8 },
	{ "F9", SDLK_F9 },
	{ "F10", SDLK_F10 },
	{ "F11", SDLK_F11 },
	{ "F12", SDLK_F12 },
	{ "MOUSE1", KEY_MOUSE1 },
	{ "MOUSE2", KEY_MOUSE2 },
	{ "MOUSE3", KEY_MOUSE3 },
};

int Keys_StringToKeyNum(char *str)
{
	keyname_t *kn;

	if (!str[1])
	{
		return tolower(str[0]);
	}
	else
	{
		for (kn = keynames; kn->name; kn++)
		{
			if (!strcmp(kn->name, str))
			{
				return kn->keynum;
			}
		}
	}

	return -1;
}

void Keys_Bind_f()
{
	if (Command_Argc() < 3)
	{
		Print("Usage : bind <key> <cmd>");
	}

	int key = Keys_StringToKeyNum(Command_Argv(1));

	if (key == -1)
	{
		Print("%s is a invalid key", Command_Argv(1));
		return;
	}

	keys[key].binding = Command_Argv(2);
}

char* Keys_GetBinding(int keynum)
{
	return keys[keynum].binding;
}

void Keys_ExecBinding(int key, bool down)
{
	char buf[1024], *p = buf, *end;
	if (!keys[key].binding || !keys[key].binding[0])
		return;

	strncpy(buf, keys[key].binding, sizeof(buf));

	while (1)
	{
		while (isspace(*p))
			p++;
		end = strchr(p, ';');
		if (end)
			*end = '\0';

		if (*p == '+')
		{
			char cmd[1024];
			sprintf(cmd, "%c%s %d", (down) ? '+' : '-', p + 1, key);
			Command_Exec(cmd);
		}
		else if (down)
		{
			Command_Exec(p);
		}
		if (!end)
			break;
		p = end + 1;
	}
}

void Client_KeyDownEvent(int key)
{
	keys[key].pressed = true;

	Keys_ExecBinding(key, true);
}

void Client_KeyUpEvent(int key)
{
	keys[key].pressed = false;

	Keys_ExecBinding(key, false);
}

void Client_KeyEvent(int key, bool down)
{
	if (down)
		Client_KeyDownEvent(key);
	else
		Client_KeyUpEvent(key);
}

void Client_Init_Input()
{
	Command_Add("bind", Keys_Bind_f);
}