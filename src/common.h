
#ifndef __COMMON_H
#define __COMMON_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shared.h"

/*
MAIN
*/

void Init(char* command);
void Frame();
void Shutdown();
void Print(char* format, ...);
void Print_Error(int type, char* format, ...);
char* CopyString(char* str);

/*
CONSOLE
*/

void ConsolePrint(char* msg);

/*
CVAR
*/

void Cvar_Init(void);
//Initialize cvar system

Cvar *Cvar_Get(char* var_name);
//Get Cvar with the name

void Cvar_Set(char* var_name, char* var_value, int var_flag, char* var_desc);
//Set Cvar with name, value in string, flag and description

void Cvar_Print(char* var_name);
//Print Cvar with his value plus description if there is one

int Cvar_GetInt(char* var_name);
//Return value of Cvar in int

float Cvar_GetFloat(char* var_name);
//Return value of Cvar in float

char* Cvar_GetString(char* var_name);
//Return value of Cvar in char*

void Cvar_Reset(char* var_name);
//Reset the Cvar to his degault value

#endif