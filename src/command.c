#include "common.h"

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

	char * pch;
	pch = strtok(CopyString(cmd), " ");
	while (pch != NULL)
	{
		if (argc == MAX_ARGS)
			return;
		argv[argc++] = pch;
		pch = strtok(NULL, " ");
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

void Command_Exec_f()
{
	char* cmd_exec;
	int i = 0;

	if (Command_Argc() < 2)
	{
		Print("Usage : exec <file>");
		return;
	}
	
	char* read = File_Read(Command_Argv(1));

	if (read == NULL)
	{
		return;
	}

	cmd_exec = malloc(sizeof(char) * 256);

	if (read)
	{
		while (*read != '\0')
		{
			if (*read == ';' || *read == '\n')
			{
				cmd_exec[i] = '\0';
				Command_Exec(cmd_exec);
				i = 0;
			}
			else
			{
				if (i < 256)
					cmd_exec[i] = *read;
				i++;
			}
			*read++;
		}
	}
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

void Command_Init()
{
	Print("Initiliazing commands");
	Command_Add("cmdlist", Command_List_f);
	Command_Add("exec", Command_Exec_f);
	Print("Commands initialized");
}