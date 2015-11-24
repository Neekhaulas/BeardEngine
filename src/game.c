#include "common.h"
#include <vector>
#include <fcntl.h>
#include <stdio.h>

std::vector<static_entity*> static_entities;
static_entity* creating_entity;
GLuint actual_texture;
beboolean editing;
beboolean map_opened;
char* map_name;
int mouseX;
int mouseY;

void Game_New_Map()
{
	Print("New map");
	if (Command_Argc() != 2)
	{
		Print("usage : newmap <mapname>");
		return;
	}
	map_name = Command_Argv(1);
	FILE* list;
	list = fopen("data/textures/textures.txt", "r");
	char* fileName = (char*)malloc(sizeof(char) * 256);
	char* file = (char*)malloc(sizeof(char) * 256);
	int size;
	actual_texture = 1;
	Print("Loading all textures");
	fscanf(list, "%d", &size);
	for (int i = 0; i < size; i++)
	{
		fscanf(list, "%s", fileName);
		_snprintf(file, 256, "data/textures/%s", fileName);
		Texture_Load(file);
	}
	fclose(list);
	map_opened = btrue;
}

void Game_Reset_Map()
{
	map_opened = bfalse;
	map_name = NULL;
	Texture_Unload_All();
	static_entities.clear();
}

void Game_Save_Map()
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

			static_entity ent;
			ent.id = i;
			ent.position = static_entities.at(i)->position;
			ent.scale = static_entities.at(i)->scale;
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
		*/

		write(f, &version, sizeof(int));
		write(f, "Faille du temps\0", sizeof(char) * 64);
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
}

void Game_Load_Map(char* mapName)
{
	Game_Reset_Map();
	Print("Loading map : %s", mapName);
	map_name = mapName;
	int f = open(mapName, _O_BINARY | _O_RDONLY);

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
		static_entity *ent = new static_entity;
		read(f, ent, sizeof(static_entity));
		ent->tex = texture_map[ent->tex];
		//Print("ID : %d Pos x : %f Pos y : %f size x : %f size y : %f texture : %d scale x : %f scale y : %f", ent.id, ent.position.x, ent.position.y, ent.size.x, ent.size.y, ent.tex, ent.scale.x, ent.scale.y);
		static_entities.push_back(ent);
	}
	close(f);

	Print("Size entities %d", static_entities.size());

	map_opened = btrue;
}

void Game_Toggle_Editor()
{
	if (!editing)
	{
		Print("Editor mode activated");
		editing = btrue;
		creating_entity = new static_entity();
	}
	else
	{
		Print("Editor mode deactivated");
		delete creating_entity;
		creating_entity = NULL;
		editing = bfalse;
	}
}

void Game_Map_Change_Texture(GLuint id)
{
	texture_t* tex;
	tex = Texture_Get(id);
	creating_entity->tex = tex->textureId;
	if (creating_entity->tex == NULL)
		return;
	creating_entity->scale.x = 1;
	creating_entity->scale.y = 1;
	creating_entity->size.x = tex->w;
	creating_entity->size.y = tex->h;
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

void Attack()
{
	if (editing && map_opened)
	{
		texture_t* tex;
		tex = Texture_Get(actual_texture);
		creating_entity->position.x = mouseX;
		creating_entity->position.y = mouseY;
		static_entities.push_back(creating_entity);
		creating_entity = new static_entity();
		creating_entity->tex = tex->textureId;
		creating_entity->scale.x = 1;
		creating_entity->scale.y = 1;
		creating_entity->size.x = tex->w;
		creating_entity->size.y = tex->h;
	}
}

void Game_Init()
{
	editing = bfalse;
	map_opened = bfalse;
	Command_Add("texture_next", Texture_Next);
	Command_Add("texture_prev", Texture_Prev);
	Command_Add("toggle_editor", Game_Toggle_Editor);
	Command_Add("newmap", Game_New_Map);
	Command_Add("savemap", Game_Save_Map);
	Command_Add("+attack", Attack);
}

void Game_Update_World(int actualTime, int lastTime)
{
	Client_S2C();
}

void Game_Render()
{
	for (unsigned int i = 0; i < static_entities.size(); i++)
	{
		Texture_Draw(static_entities.at(i)->tex, static_entities.at(i)->size.x, static_entities.at(i)->size.y, static_entities.at(i)->scale.x, static_entities.at(i)->scale.y, static_entities.at(i)->position.x, static_entities.at(i)->position.y, editing);
	}
	if (creating_entity != NULL)
	{
		Texture_Draw(creating_entity->tex, creating_entity->size.x, creating_entity->size.y, creating_entity->scale.x, creating_entity->scale.y, mouseX, mouseY, editing);
	}
}

void Game_Mouse_Move(int x, int y)
{
	mouseX = x;
	mouseY = y;
}

void Game_Mouse_Wheel(int value)
{
	if (editing)
	{
		creating_entity->scale.x += (value * creating_entity->scale.x / 10.0f);
		creating_entity->scale.y += (value * creating_entity->scale.y / 10.0f);
	}
	else
	{

	}
}