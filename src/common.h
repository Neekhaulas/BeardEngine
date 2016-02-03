#pragma once

#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <enet/enet.h>
#include <map>
#include <vector>
#include <physfs.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

#include <chrono>

#include "shared.h"
#include "keys.h"
#include "platform.h"

#ifndef SERVER
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
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
void Clamp(float& value, float min, float max);

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

bool Cvar_Command();
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

/*ENTITY*/

void Entity_Update(dynamic_entity *ent, int delta);
void Entity_Resolve_Collision(dynamic_entity *ent1, entity *ent2);
double Entity_Distance(entity *ent1, entity *ent2);

/*COLLISION*/

bool Collision_AABB_Entity(entity* ent1, entity* ent2);
bool Collision_AABB_Entity_Offset(entity* ent1, entity* ent2, float& moveX, float& moveY);

#ifndef SERVER

/*CLIENT*/

void Client_KeyEvent(int key, bool down);
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
void Client_Send_Request_Connect();
void Client_Send_Input(int actualTime);
//void Client_Unpack_Snapshot(snapshot s);

/*TEXTURE*/

void Texture_Draw(GLuint tex, float w, float h, float x, float y, int debug);
GLuint Texture_Load(char* nameFile);
texture_t* Texture_Get(unsigned int id);
void Texture_Unload_All();

/*RENDER*/
void Render_Init();
bool Render_InitGL();
void Render_Draw_Frame();
#endif

/*GAME*/

void Game_Init();
void Game_Update_World(int actualTime, int lastTime);
void Game_Reset_Map();
void Game_Load_Map(char* mapName);
void Game_Render();
void Game_Mouse_Move(int x, int y);
void Game_Mouse_Wheel(int value);
std::vector<dynamic_entity*> Game_Get_Entities();
void Game_Frame(int time, int lastTime);
void Game_Start();
bool Game_Is_Started();

/*SERVER*/

bool Server_Init(int argc, char** argv);
void Server_Cleanup(void);
void Server_Frame();
void Server_Send_Game_State();
void Server_Send_Infos(int clientNumber);
void Server_Disconnect_Player(int clientNumber, int reason);
void Server_Send_To(ENetPeer* peer, const uint8 *source, uint32 length, uint8 channelNo, uint32 flag);
void Server_Handle_Packet(ENetPacket* packet, ENetPeer* peer, int client, int chan);
void Server_Send_Game_Infos(ENetPeer* peer, int team);
void Server_Send_Waiting_For_Start(ENetPeer* peer);
void Server_Think();
void Server_Make_Snapshot(Client *client, int actualTime);
int Server_Count_Client();
Client* Server_Get_Client(int client);

enum {DISCONNECT = 0, DISCONNECT_NOTAUTH, DISCONNECT_MAXCLIENTS, DISCONNECT_AFK, DISCONNECT_CHEAT, DISCONNECT_WRONG_VERSION};
enum {CHL_S2C = 1, CHL_C2S};
