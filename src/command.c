#include "common.h" 
#include <string.h>
#include <stdio.h>

#define MAX_ARGS 10

static int argc = 0;
static char* argv[MAX_ARGS];

struct _command
{
	command *next;
	char *command_text;
	callback function;
};

static command* commands;

void Command_Parse(const char* cmd)
{
	argc = 0;

	int size, i;
	char line[1024];
	char *cmd_str = CopyString(cmd);
	char *str;
	beboolean inQuote;

	size = strlen(cmd_str);
	inQuote = bfalse;

	while (size)
	{
		str = cmd_str;
		for (i = 0; i < size; i++)
		{
			if (*(cmd_str + i) == ' ' && !inQuote)
			{
				break;
			}

			if (*(cmd_str + i) == '"')
			{
				if (!inQuote)
				{
					inQuote = btrue;
					i++;
					size -= i;
					memmove(str, str + i, size);
				}
				else
				{
					inQuote = bfalse;
					break;
				}
			}
		}

		memcpy(line, str, i);
		line[i] = 0;
		argv[argc++] = CopyString(line);
		if (argc == MAX_ARGS)
			break;

		if (i == size)
			size = 0;
		else
		{
			i++;
			size -= i;
			memmove(str, str + i, size);
		}
	}
}

int Command_Argc()
{
	return argc;
}

char* Command_Argv(int index)
{
	if (index >= argc)
	{
		return "";
	}
	return argv[index];
}

void Command_Add(const char* command_name, void* function)
{
	command* cmd;

	if (Command_Find(command_name))
	{
		Print("Command %s already exist", command_name);
		return;
	}

	cmd = malloc(sizeof(command));
	cmd->command_text = CopyString(command_name);
	cmd->function = function;
	cmd->next = commands;

	commands = cmd;
}

command* Command_Find(const char* command_name)
{
	command* cmd;
	for (cmd = commands; cmd; cmd = cmd->next)
	{
		if (!strcmp(command_name, cmd->command_text))
		{
			return cmd;
		}
	}
	return NULL;
}

void Command_Exec(const char* text)
{
	command *cmd = NULL, *prev = NULL, *next = NULL;

	Command_Parse(text);

	if (!Command_Argc())
	{
		return;
	}

	for (cmd = commands; cmd; cmd = cmd->next)
	{
		if (!strcmp(cmd->command_text, Command_Argv(0)))
		{
			if (prev != NULL)
			{
				next = cmd->next;
				prev->next = next;
				cmd->next = commands;
				commands = cmd;
				if (!cmd->function)
				{
					return;
				}
				cmd->function();
				return;
			}

			if (!cmd->function)
			{
				return;
			}
			cmd->function();
			return;
		}
		prev = cmd;
	}

	if (Cvar_Command())
	{
		return;
	}

	Print("Command %s not found", Command_Argv(0));

	return;
}

void Command_List_f()
{
	command* cmd;

	Print("============= List of commands ============");

	for (cmd = commands; cmd; cmd = cmd->next)
	{
		Print("%s", cmd->command_text);
	}
}

void Command_Exec_f()
{
	if (Command_Argc() == 2)
	{
		file_t *file = File_Read(Command_Argv(1));
		if (file)
		{
			int i;
			char line[1024];
			char *str;
			while (file->current_size)
			{
				str = file->data;

				for (i = 0; i < file->current_size; i++)
				{
					if (*(str + i) == '\n')
					{
						break;
					}
				}

				memcpy(line, str, i);
				line[i] = 0;
				Command_Exec(line);

				if (i == file->current_size)
					file->current_size = 0;
				else
				{
					i++;
					file->current_size -= i;
					memmove(str, str + i, file->current_size);
				}
			}
		}
	}
	else
	{
		Print("usage : exec <file>");
	}
}


void Echo_f()
{
	if (Command_Argc() == 2)
	{
		Print(Command_Argv(1));
	}
	else
	{
		Print("usage: echo <text>");
	}
}

void Command_Init()
{
	Print("Initiliazing commands");
	Command_Add("cmdlist", Command_List_f);
	Command_Add("exec", Command_Exec_f);
	Command_Add("echo", Echo_f);
	Print("Commands initialized");
}