#include "common.h"
#include <fcntl.h>
#include "hero.h"

std::vector<static_entity*> static_entities;
std::vector<dynamic_entity*> dynamic_entities;
bool map_opened;
char* map_name;
int mouseX;
int mouseY;
int id(0);
bool gameStarted(false);

bool Game_Is_Started()
{
	return gameStarted;
}

std::vector<dynamic_entity*> Game_Get_Entities()
{
	return dynamic_entities;
}

void Game_Frame(int time, int lastTime)
{
	Game_Update_World(time, lastTime);
}

void Game_Init()
{
	map_opened = false;
	id = 0;
	Hero hero;
	int test = open("test.hero", O_RDONLY | O_BINARY);
	if (test > 0)
	{
		read(test, &hero, sizeof(Hero));
		close(test);
		Print("Test : %f", hero.getAD());
	}
}

bool Game_Entity_Exists(int id)
{
	for (int i = 0; i < dynamic_entities.size(); i++)
	{
		if (dynamic_entities.at(i)->id == id)
		{
			return true;
		}
	}
	return false;
}
int test;
void Game_Update_World(int actualTime, int lastTime)
{
#ifdef SERVER
	Server_Think();

	if (actualTime - test > 1000)
	{
		dynamic_entities.push_back(new dynamic_entity(++id, ET_GENERAL));
		Print("New entity");
		test = actualTime;
	}
#endif
	
	//Game_Update_Physics();
}

#ifdef SERVER
void Game_Start()
{
	for (int i = 0; i < Server_Count_Client(); i++)
	{
		Server_Get_Client(i)->c = new character(i);
	}
	gameStarted = true;
}

void Game_Reset_Map()
{
	map_opened = false;
	map_name = NULL;
	static_entities.clear();
	dynamic_entities.clear();
}

/*void Game_Save_Map()
{
	texture_t* tex;
	int f;
	unsigned int count_entities = 0;
	unsigned int count_textures = 0;
	Print("Saving map in %s", map_name);
	f = open(map_name, _O_CREAT | _O_RDWR | _O_BINARY);
	if (f > 0)
	{
		int version = 1;
		std::map<char*, unsigned int> list_textures;
		std::vector<static_entity> map_entities;

		for (int i = 1; i < static_entities.size(); i++)
		{
			tex = Texture_Get(static_entities.at(i)->tex);
			if (list_textures.count(tex->name) == 0)
			{
				list_textures[tex->name] = count_textures++;
			}

			static_entity ent(0);
			ent.id = i;
			ent.position = static_entities.at(i)->position;
			ent.size = static_entities.at(i)->size;
			ent.tex = list_textures[tex->name];
			map_entities.push_back(ent);
		}

		/*
		Description of the save
		- Version of the game
		- Map name
		- Number of textures
		- All the names of textures
		- Number of entities
		- All the entities
		

		write(f, &version, sizeof(int));
		write(f, "Faille du temps", sizeof(char) * 64);
		write(f, &count_textures, sizeof(unsigned int));
		for (std::map<char*, unsigned int>::iterator it = list_textures.begin(); it != list_textures.end(); it++)
		{
			write(f, it->first, sizeof(char) * 256);
			write(f, &it->second, sizeof(unsigned int));
		}

		count_entities = map_entities.size() + 1;

		write(f, &count_entities, sizeof(unsigned int));
		for (unsigned int i = 0; i < map_entities.size(); i++)
		{
			write(f, &map_entities.at(i), sizeof(static_entity));
		}
		close(f);
		return;
	}
	Print("Impossible d'ouvrir le ficher %s", map_name);
}*/

void Game_Load_Map(char* mapName)
{
	Game_Reset_Map();
	Print("Loading map : %s", mapName);
	map_name = mapName;
	int f = open(mapName, O_BINARY | O_RDONLY);

	int version;
	char name[64];
	unsigned int count_entities;
	unsigned int count_textures;

	if (f == -1)
	{
		Print("Cannot open %s", mapName);
		return;
	}

	read(f, &version, sizeof(int));
	read(f, name, sizeof(char) * 64);
	read(f, &count_textures, sizeof(unsigned int));

	read(f, &count_entities, sizeof(unsigned int));
	for (unsigned int i = 0; i < count_entities; i++)
	{
		static_entity *ent = new static_entity();
		read(f, ent, sizeof(static_entity));
		static_entities.push_back(ent);
	}
	close(f);

	map_opened = true;
}

void Attack()
{

}

#else

void Game_Render()
{
	for (unsigned int i = 0; i < static_entities.size(); i++)
	{
		Texture_Draw(static_entities.at(i)->tex, static_entities.at(i)->size.x, static_entities.at(i)->size.y, static_entities.at(i)->position.x, static_entities.at(i)->position.y, 0);
	}

	for (unsigned int i = 0; i < dynamic_entities.size(); i++)
	{
		glLoadIdentity();
		glOrtho(0, 800, 600, 0, 0, 100);
		glTranslatef(dynamic_entities.at(i)->position.x, dynamic_entities.at(i)->position.y, 0);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINES);
		glVertex3f(dynamic_entities.at(i)->size.x, 0, 0.0f);
		glVertex3f(0, 0, 0.0f);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(0, 0, 0.0f);
		glVertex3f(0, dynamic_entities.at(i)->size.y, 0.0f);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(0, dynamic_entities.at(i)->size.y, 0.0f);
		glVertex3f(dynamic_entities.at(i)->size.x, dynamic_entities.at(i)->size.y, 0.0f);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(dynamic_entities.at(i)->size.x, dynamic_entities.at(i)->size.y, 0.0f);
		glVertex3f(dynamic_entities.at(i)->size.x, 0, 0.0f);
		glEnd();
	}
}

void Game_Mouse_Move(int x, int y)
{
	mouseX = x;
	mouseY = y;
}

void Game_Mouse_Wheel(int value)
{

}

void Game_Reset_Map()
{
	map_opened = false;
	map_name = NULL;
	Texture_Unload_All();
	static_entities.clear();
	dynamic_entities.clear();
}

void Game_Load_Map(char* mapName)
{
	Game_Reset_Map();
	Print("Loading map : %s", mapName);
	map_name = mapName;
	int f = open(mapName, O_BINARY | O_RDONLY);

	int version;
	char name[64];
	unsigned int count_entities;
	unsigned int count_textures;
	std::map<unsigned int, GLuint> texture_map;

	if (f == -1)
	{
		Print("Cannot open %s", mapName);
		return;
	}

	read(f, &version, sizeof(int));
	read(f, name, sizeof(char) * 64);
	read(f, &count_textures, sizeof(unsigned int));

	Print("%d", count_textures);

	for (unsigned int i = 0; i < count_textures; i++)
	{
		char texture_name[256];
		unsigned int texture_id;
		read(f, texture_name, sizeof(char) * 256);
		read(f, &texture_id, sizeof(unsigned int));
		texture_map[texture_id] = Texture_Load(texture_name);
	}

	read(f, &count_entities, sizeof(unsigned int));
	for (unsigned int i = 0; i < count_entities; i++)
	{
		static_entity *ent = new static_entity();
		read(f, ent, sizeof(static_entity));
		ent->tex = texture_map[ent->tex];
		static_entities.push_back(ent);
	}
	close(f);

	map_opened = true;
}


#endif
