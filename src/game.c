#include "common.h"
#include <vector>
#include <fcntl.h>
#include <stdio.h>

std::vector<static_entity*> static_entities;
static_entity* creating_entity;
GLuint actual_texture;
beboolean editing;

void Game_Load_Map(char* mapName)
{
	Texture_Unload_All();
	int f = open(mapName, _O_BINARY | _O_RDONLY);

	if (f == -1)
	{
		Print("Cannot open %s", mapName);
		f = open(mapName, _O_BINARY | _O_CREAT | _O_WRONLY);
		int version = 1;
		static_entity test = static_entity();
		test.position.x = 50;
		test.position.y = 230;

		write(f, &version, sizeof(int));
		write(f, "Faille du temps\0", sizeof(char) * 64);
		write(f, &test, sizeof(static_entity));
		close(f);
		return;
	}

	FILE* list;
	list = fopen("data/textures/textures.txt", "r");
	char* fileName = (char*)malloc(sizeof(char)* 256);
	char* file = (char*)malloc(sizeof(char) * 256);
	int size;
	actual_texture = 1;

	fscanf(list, "%d", &size);
	for (int i = 0; i < size; i++)
	{
		fscanf(list, "%s", fileName);
		_snprintf(file, 256, "data/textures/%s", fileName);
		Texture_Load(file);
		Print("%s", file);
	} 
	fclose(list);

	_close(f);
}

void Game_Toggle_Editor()
{
	if (!editing)
	{
		editing = btrue;
		creating_entity = new static_entity();
	}
	else
	{
		delete creating_entity;
		creating_entity = NULL;
		editing = bfalse;
	}
}

void Game_Map_Change_Texture(GLuint id)
{
	creating_entity->tex = Texture_Get(id);
	creating_entity->size.x = creating_entity->tex->w;
	creating_entity->size.y = creating_entity->tex->h;
}

void Texture_Next()
{
	if (!editing)
		return;
	Game_Map_Change_Texture(++actual_texture);
	Print("Next texture : %d", actual_texture);
}

void Texture_Prev()
{
	if (!editing)
		return;
	Game_Map_Change_Texture(--actual_texture);
	Print("Prev texture : %d", actual_texture);
}

void Game_Init()
{
	editing = bfalse;
	Command_Add("texture_next", Texture_Next);
	Command_Add("texture_prev", Texture_Prev);
	Command_Add("toggle_editor", Game_Toggle_Editor);
}

void Game_Update_World(int actualTime, int lastTime)
{
	Client_S2C();
}

void Game_Render()
{
	for (int i = 0; i < static_entities.size(); i++)
	{
		Texture_Draw(static_entities.at(i)->tex, 2, 2, 1, 1, 0, 0);
	}
	if (creating_entity != NULL)
	{
		Texture_Draw(creating_entity->tex, creating_entity->size.x, creating_entity->size.y, 1, 1, 0, 0);
	}
}

void Game_Mouse_Move(int x, int y)
{

}