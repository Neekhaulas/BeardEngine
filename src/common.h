
#ifndef __COMMON_H
#define __COMMON_H

/*
MAIN
*/

void Init(char* command);
void Frame();
void Shutdown();

/*
CONSOLE
*/

void CPrintf(char* format, ...);
void CPrintf_Error(int type, char* format, ...);

/*
CVAR
*/

void Cvar_Init(void);
//Initialize cvar system

Cvar *Cvar_Get(char* var_name);
//Get Cvar with the name

void Cvar_Set(char* var_name, char* var_value, int var_flag);
//Set Cvar with name, value in string and flaf

#endif