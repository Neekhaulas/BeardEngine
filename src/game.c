#include "common.h"
#include <vector>
#include <fcntl.h>
#include <stdio.h>

std::vector<static_entity> static_entities;
GLuint actual_texture;

void Game_Load_Map(char* mapName)
{
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

	Game_Map_Change_Texture(actual_texture);

	_close(f);
}

void Game_Map_Change_Texture(GLuint id)
{
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture_Next()
{
	Game_Map_Change_Texture(++actual_texture);
	Print("Next texture : %d", actual_texture);
}

void Texture_Prev()
{
	Game_Map_Change_Texture(--actual_texture);
	Print("Prev texture : %d", actual_texture);
}

void Game_Init()
{
	Command_Add("texture_next", Texture_Next);
	Command_Add("texture_prev", Texture_Prev);
}

void Game_Update_World(int actualTime, int lastTime)
{
	Client_S2C();
}