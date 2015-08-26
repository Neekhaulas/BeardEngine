
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
char* CopyString(const char* str);
void Game_Frame();
void Input_Frame();
void Quit();
char* Format(char *format, ...);

/*
CONSOLE
*/

#define	MAX_EDIT_LINE	256

void Console_Print(char* msg);
void Console_Init();
void Console_Frame();

/*
CVAR
*/

void Cvar_Init(void);
//Initialize cvar system

Cvar* Cvar_Get(char* var_name);
//Get Cvar with the name

Cvar* Cvar_Set(char* var_name, char* var_value, int var_flag, char* var_desc);
Cvar* Cvar_Set2(char* var_name, char* var_value, int var_flag);
//Set Cvar with name, value in string, flag and description

void Cvar_Print(Cvar* var);
//Print Cvar with his value plus description if there is one

int Cvar_GetInt(char* var_name);
//Return value of Cvar in int

float Cvar_GetFloat(char* var_name);
//Return value of Cvar in float

char* Cvar_GetString(char* var_name);
//Return value of Cvar in char*

void Cvar_Reset(char* var_name);
//Reset the Cvar to his degault 

beboolean Cvar_Command();
//if the last command is a Cvar

/*
COMMAND
*/

typedef void(*callback) (void);

void Command_Add(const char* command_name, void* function);
command* Command_Find(const char* command_name);
void Command_Init();
void Command_Exec(const char* command_name);
char* Command_Argv(int index);
int Command_Argc();
void Command_Parse(const char* cmd);

/*
FILE
*/

char* File_Read(char *name);

/*
EVENT
*/

#define MAX_EVENTS 256

typedef enum
{
	EVT_KEY,
	EVT_CHAT,
	EVT_MOUSE,
	EVT_JOYSTICK
} eventType;

void Event_Queue(eventType type, int value1, int value2);
void Event_Loop();

/*
NETWORK
*/

void Network_OpenIP();
void Network_Config(beboolean enableNetworking);
void Network_Init();

#endif