#include "common.h"
#include <vector>
#include <io.h>
#include <fcntl.h>

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

	_close(f);
}

void Game_Update_World(int actualTime, int lastTime)
{
	Client_S2C();
}