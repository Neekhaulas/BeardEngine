#include "client_input.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

key keys[MAX_KEYS];

int Keys_StringToKeyNum(char *str)
{
	if (!str[1])
	{
		return tolower(str[0]);
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

void Keys_ExecBinding(int key, beboolean down)
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
	keys[key].pressed = btrue;

	Keys_ExecBinding(key, btrue);
}

void Client_KeyUpEvent(int key)
{
	keys[key].pressed = bfalse;

	Keys_ExecBinding(key, bfalse);
}

void Client_KeyEvent(int key, beboolean down)
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