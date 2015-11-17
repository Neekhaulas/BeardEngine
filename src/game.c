#include "common.h"
#include <vector>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>

std::vector<static_entity> static_entities;

void Game_Load_Map(char* mapName)
{
	int f = _open(mapName, _O_BINARY | _O_RDONLY);

	if (f == -1)
	{
		Print("Cannot open %s", mapName);
		f = _open(mapName, _O_BINARY | _O_CREAT | _O_WRONLY);
		int version = 1;
		static_entity test = static_entity();
		test.position.x = 50;
		test.position.y = 230;

		_write(f, &version, sizeof(int));
		_write(f, "Faille du temps\0", sizeof(char) * 64);
		_write(f, &test, sizeof(static_entity));
		_close(f);
		return;
	}

	FILE* list;
	list = fopen("data/textures/textures.txt", "r");
	char* fileName = (char*)malloc(sizeof(char)* 256);
	char* file = (char*)malloc(sizeof(char) * 256);
	int size;

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

void Game_Update_World(int actualTime, int lastTime)
{
	Client_S2C();
}