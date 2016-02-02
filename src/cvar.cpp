
#include "common.h"

#define			MAX_CVARS	1024
Cvar			cvar_indexes[MAX_CVARS];
int				cvar_numIndexes;

#define			HASH_SIZE	256
static	Cvar	*hashTable[HASH_SIZE];

int Hash(const char *string)
{
	int hash = 0;
	int c;

	while (c = *string++)
	{
		hash += c + 175;
	}

	hash &= (HASH_SIZE-1);

	return hash;
}

Cvar* Cvar_Find(char* var_name)
{
	Cvar* var;
	int hash = Hash(var_name);
	
	for (var = hashTable[hash]; var; var = var->next) {
		if (strcmp(var_name, var->name) == 0) {
			return var;
		}
	}

	return NULL;
}

Cvar* Cvar_Get(char* var_name)
{
	Cvar* var;

	var = Cvar_Find(var_name);

	return var;
}

Cvar* Cvar_Set(char* var_name, char* var_value, int var_flag, char* var_desc)
{
	Cvar* var;
	int index;
	int hash;

	var = Cvar_Find(var_name);

	if (var)
	{
		if (var->flags & CVAR_READ_ONLY)
		{
			Print("%s var is read only", var_name);
			return var;
		}

		if (var->flags & CVAR_LOCKED && !(var_flag & CVAR_LOCKED))
		{
			Print("%s var is locked", var_name);
			return var;
		}

		var->string = CopyString(var_value);
		var->value = atoi(var_value);
		var->valuef = atof(var_value);
		var->flags = var_flag;
		var->modified = true;
		var->countModified = 1;
		return var;
	}

	for (index = 0; index < MAX_CVARS; index++)
	{
		if (!cvar_indexes[index].name)
			break;
	}

	if (index >= MAX_CVARS)
	{
		Print("Error: Too many cvars, cannot create a new one!");
		return NULL;
	}

	var = &cvar_indexes[index];
	var->name = var_name;
	var->reset = CopyString(var_value);
	var->string = CopyString(var_value);
	var->value = atoi(var_value);
	var->valuef = atof(var_value);
	var->flags = var_flag;
	var->modified = true;
	var->countModified = 1;
	var->desc = var_desc;

	hash = Hash(var_name);

	var->hashIndex = hash;
	var->next = hashTable[hash];
	if (hashTable[hash])
		hashTable[hash]->prev = var;

	var->prev = NULL;
	hashTable[hash] = var;

	return var;
}

Cvar* Cvar_Set2(char* var_name, char* var_value, int var_flag)
{
	return Cvar_Set(var_name, var_value, var_flag, NULL);
}

void Cvar_Print(Cvar* var)
{
	if (var)
	{
		if (var->flags & CVAR_READ_ONLY || var->flags & CVAR_PROTECTED)
		{
			Print("\"%s\" : \"%s\"", var->name, var->string);
		}
		else
		{
			if (var->desc)
			{
				Print("\"%s\" : \"%s\" (default : %s) (%s)", var->name, var->string, var->reset, var->desc);
			}
			else
			{
				Print("\"%s\" : \"%s\" (default : %s)", var->name, var->string, var->reset);
			}
		}
	}
}

int Cvar_GetInt(char* var_name)
{
	Cvar* var;

	var = Cvar_Find(var_name);

	if (!var)
		return 0;
	return var->value;
}

float Cvar_GetFloat(char* var_name)
{
	Cvar* var;

	var = Cvar_Find(var_name);

	if (!var)
		return 0;
	return var->valuef;
}

char* Cvar_GetString(char* var_name)
{
	Cvar* var;

	var = Cvar_Find(var_name);

	if (!var)
		return "";
	return var->string;
}

void Cvar_Reset(char* var_name)
{
	Cvar* var;
	
	var = Cvar_Find(var_name);


	if (var)
	{
		if (var->flags & CVAR_PROTECTED)
		{
			return;
		}

		if (var->flags & CVAR_READ_ONLY)
		{
			return;
		}

		var->string = var->reset;
		var->value = atoi(var->reset);
		var->valuef = atof(var->reset);
		var->modified = true;
		var->countModified++;
	}
}

bool Cvar_Command()
{
	Cvar *cvar;

	cvar = Cvar_Find(Command_Argv(0));
	if (!cvar)
	{
		return false;
	}

	if (Command_Argc() == 1)
	{
		Cvar_Print(cvar);
		return true;
	}

	Cvar_Set(cvar->name, Command_Argv(1), 0, NULL);

	return true;
	//set
}

void Cvar_Print_f()
{
	Cvar *cvar;

	if (Command_Argc() < 2)
	{
		Print("Usage : print <variable>");
	}

	cvar = Cvar_Find(Command_Argv(1));

	if (cvar)
		Cvar_Print(cvar);
	else
		Print("Cvar %s doesn't exist.", Command_Argv(1));
}

void Cvar_Set_f()
{
	Cvar *cvar;

	if (Command_Argc() < 2)
	{
		Print("set <cvar> <value>");
		return;
	}

	if (Command_Argc() == 2)
	{
		Cvar_Print_f();
		return;
	}

	cvar = Cvar_Find(Command_Argv(1));
	if (!cvar)
	{
		Cvar_Set(Command_Argv(1), Command_Argv(2), 0, NULL);
		return;
	}

	Cvar_Set(cvar->name, Command_Argv(2), CVAR_USER_CREATED, NULL);
}

void Cvar_Reset_f()
{
	if (Command_Argc() < 2)
	{
		Print("Usage : reset <cvar>");
	}	
}

void Cvar_List_f()
{
	int i = 0, c = 0;
	Cvar *cvar;
	for (i = 0; i < HASH_SIZE; i++)
	{
		if (hashTable[i])
		{
			for (cvar = hashTable[i]; cvar; cvar = cvar->next)
			{
				Print("%s", cvar->name);
				c++;
			}
		}
	}
	Print("Total : %d cvars", c);
}

void Cvar_Init()
{
	memset(cvar_indexes, '\0', sizeof(cvar_indexes));
	memset(hashTable, '\0', sizeof(hashTable));

	Command_Add("set", Cvar_Set_f);
	Command_Add("reset", Cvar_Reset_f);
	Command_Add("cvarlist", Cvar_List_f);
	Command_Add("print", Cvar_Print_f);
}
