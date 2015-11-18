
#ifndef __COMMON_H
#define __COMMON_H

#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <enet/enet.h>
#include <map>

#include "shared.h"
#include "keys.h"
#include "platform.h"

#ifndef SERVER
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <gl/glew.h>
#include <SDL_opengl.h>
#include <gl/GLU.h>
#endif

/*
MAIN
*/

int Init(char* command);
void Frame();
void Shutdown();
void Print(char* format, ...);
void Print_Error(int type, char* format, ...);
char* CopyString(const char* str);
void Game_Frame();
void Input_Frame();
void Quit();

/*
CONSOLE
*/

#define	MAX_EDIT_LINE	256

void Console_Print(char* msg);
void Console_Init();
void Console_Frame();

/*CVAR*/

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

/*COMMAND*/
typedef void(*callback) ();

void Command_Add(const char* command_name, callback function);
command* Command_Find(const char* command_name);
void Command_Init();
void Command_Exec(const char* command_name);
char* Command_Argv(int index);
int Command_Argc();
void Command_Parse(const char* cmd);

/*FILE*/

typedef struct
{
	char* data;
	int max_size;
	int current_size;
} file_t;

file_t* File_Read(char *name);

/*EVENT*/

void Event_Queue(int event_type, int value1, int value2);
void Event_Loop();
event Event_Get();

#ifndef SERVER

/*CLIENT*/

void Client_KeyEvent(int key, beboolean down);
void Client_Init();
void Client_Process_Events();
void Client_Disconnect();
void Client_Connect();
void Client_Connect_f();
void Client_S2C();
void Client_Send_Infos();
void Client_Cleanup();
void Client_Abort_Connection();
void Client_Handle_Packet(enet_uint8 chanel, ENetPacket* packet);
void Client_Send(const uint8 *source, uint32 length, uint8 channelNo, uint32 flag);

/*GAME*/

void Game_Init();
void Game_Update_World(int actualTime, int lastTime);
void Game_Reset_Map();
void Game_Load_Map(char* mapName);

//This methods are callable only in map editor

void Game_Map_Change_Texture(GLuint id);

/*TEXTURE*/

GLuint Texture_Load(char* nameFile);
texture_t* Texture_Get(unsigned int id);

/*RENDER*/
void Render_Init();
beboolean Render_InitGL();
void Render_Draw_Frame();
#endif

/*SERVER*/

beboolean Server_Init(int argc, char** argv);
void Server_Cleanup(void);
void Server_Frame();
void Server_Send_Game_State();
void Server_Send_Infos(int clientNumber);
void Server_Disconnect_Player(int clientNumber, int reason);
void Server_Send_To(ENetPeer* peer, const uint8 *source, uint32 length, uint8 channelNo, uint32 flag);

typedef struct _Client
{
	int clientNumber;
	ENetPeer *peer;
	int team;
	int character;
	int skin;
	int ping;
} Client;

enum {DISCONNECT = 0, DISCONNECT_NOTAUTH, DISCONNECT_MAXCLIENTS, DISCONNECT_AFK, DISCONNECT_CHEAT};
enum {CHL_S2C = 1, CHL_C2S};

#endif