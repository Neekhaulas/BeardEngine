
#include "../src/common.h"

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
		if (!stricmp(var_name, var->name)) {
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

void Cvar_Set(char* var_name, char* var_value, int var_flag, char* var_desc)
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
			return;
		}

		var->string = CopyString(var_value);
		var->value = atoi(var_value);
		var->valuef = atof(var_value);
		var->flags = var_flag;
		var->modified = btrue;
		var->countModified = 1;
		return;
	}

	for (index = 0; index < MAX_CVARS; index++)
	{
		if (!cvar_indexes[index].name)
			break;
	}

	if (index >= MAX_CVARS)
	{
		Print("Error: Too many cvars, cannot create a new one!");
	}

	var = &cvar_indexes[index];
	var->name = var_name;
	var->reset = CopyString(var_value);
	var->string = CopyString(var_value);
	var->value = atoi(var_value);
	var->valuef = atof(var_value);
	var->flags = var_flag;
	var->modified = btrue;
	var->countModified = 1;
	var->desc = var_desc;

	hash = Hash(var_name);

	var->hashIndex = hash;
	var->next = hashTable[hash];
	if (hashTable[hash])
		hashTable[hash]->prev = var;

	var->prev = NULL;
	hashTable[hash] = var;
}

void Cvar_Print(char* var_name)
{
	Cvar* var;

	var = Cvar_Find(var_name);

	if (var)
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
	else
	{
		Print("\"%s\" not found", var_name);
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
		var->modified = btrue;
		var->countModified++;
	}
}

void Cvar_Init()
{
	memset(cvar_indexes, '\0', sizeof(cvar_indexes));
	memset(hashTable, '\0', sizeof(hashTable));
}