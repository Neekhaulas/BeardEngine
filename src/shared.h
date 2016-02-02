
#ifndef __SHARED_H
#define __SHARED_H

#ifndef __GNUC__
#ifndef __attribute__
#define __attribute__(x)
#endif
#endif

#include "enet/enet.h"

typedef char int8;
typedef short int16;
typedef int int32;
typedef long long int64;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

#define PRODUCT_NAME "BeardEngine"
#define VERSION 1
#define ERROR_LEVEL 1

#define MASTERSERVER "be.grandebar.be"
#define PORT_SERVER_DEFAULT 21430

#define CLIENT_WINDOW_TITLE "BeardEngine Protoype"

#define MAX_EVENTS_QUEUED 256
#define PLAYER_PER_TEAM 1
#define TOTAL_PLAYERS PLAYER_PER_TEAM

#define MAX_ENTITIES_IN_SNAPSHOT 256
#define BACKED_SNAPSHOT 32

/*
============= VECTOR ===============
*/
class vec
{
public:
	vec()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	vec(float x = 0.0f, float y = 0.0f, float z = 0.0f)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	float x;
	float y;
	float z;
};

/*
============= CVAR =================
g - For game variable
c - For client variable
s - For server variable
d - For debug purpose
*/

#define CVAR_READ_ONLY		0x00001
#define CVAR_USER_CREATED	0x00002
#define CVAR_CHEATS			0x00004
#define CVAR_PROTECTED		0x00008
#define CVAR_LOCKED			0x00010

typedef struct _Cvar Cvar;

struct _Cvar
{
	char		*name;
	char		*string;
	char		*reset;
	char		*desc;
	int			value;
	float		valuef;
	int			countModified;
	bool	modified;
	int			flags;

	Cvar		*next;
	Cvar		*prev;
	int			hashIndex;
};

/*
============== ENTITY =============
*/

typedef enum entityType
{
	ET_GENERAL,
	ET_PLAYER,
	ET_MINION,
	ET_UNIT,
	ET_ITEM,
	ET_PROJECTILE,
	ET_BEAM
} entityType;

/*
============= COMMAND ==============
*/

typedef struct _command command;

/*
============= EVENT ================
*/

typedef enum
{
	EVENT_KEY = 0,
	EVENT_MOUSE,
	EVENT_CHAR,
	EVENT_JOYSTICK,
	EVENT_NULL
} eventType;

typedef struct 
{
	eventType event_type;
	int value1, value2;
} event;

/*
============= ENTITY ================
*/

class entity
{
public:
	entity() : id(0), position(0, 0), size(0, 0), origin(0, 0), type(ET_GENERAL) {};
	entity(int _id, entityType _type) : id(_id), position(0, 0), size(0, 0), origin(0, 0), type(_type) {};
	int id;
	entityType type;
	vec position;
	vec size;
	vec origin;
	unsigned int tex;
};

class static_entity : public entity
{
public:
	static_entity() : entity(0, ET_GENERAL) {};
};

class dynamic_entity : public entity
{
public:
	dynamic_entity() : applyGravity(true), collide(true), velocity(0, 0), gravity(0, 0), entity(0, ET_GENERAL) {};
	dynamic_entity(int id, entityType type) : applyGravity(true), collide(true), velocity(0, 0), gravity(0, 0), entity(id, type){};
	vec velocity;
	vec gravity;
	bool applyGravity;
	bool collide;
	bool hasGravity(){ return applyGravity; }
	bool needCollide(){ return collide; }
};

/*
============ USERCMD ==================
*/

class usercmd
{
public:
	usercmd() : lerp(0), horizontalMove(0), angle(0), button(0) {};
	usercmd(short _lerp, float _horizontalMove, float _angle, int _button) : lerp(_lerp), horizontalMove(_horizontalMove), angle(_angle), button(_button) {};
	short lerp;
	float horizontalMove;
	float angle;
	int button;
};

/*
============= UNIT ====================
*/

class unit : public dynamic_entity
{
public:
	unit(int id) : dynamic_entity(id, ET_UNIT) {};
};

/*
============= PLAYER ==================
*/

class character : public unit
{
public:
	character(int id) : ad(0), ap(0), hp(0), mp(0), armor(0), mr(0), cdr(0), moveSpeed(0), attackSpeed(0), regenHP(0), regenMP(0),
		ad_per_level(0), ap_per_level(0), hp_per_level(0), mp_per_level(0), armor_per_level(0), mr_per_level(0), cdr_per_level(0), moveSpeed_per_level(0), attackSpeed_per_level(0), regenHP_per_level(0), regenMP_per_level(0), unit(id) { type = ET_PLAYER; };
	float ad, ap, hp, mp, armor, mr, cdr, moveSpeed, attackSpeed, regenHP, regenMP,
		ad_per_level, ap_per_level, hp_per_level, mp_per_level, armor_per_level, mr_per_level, cdr_per_level, moveSpeed_per_level, attackSpeed_per_level, regenHP_per_level, regenMP_per_level;

};

/*
============= COLLISION ===============
*/

/*
============= OPCODES =================
*/

enum PacketCmd {
	C2S_COMMAND = 1,
	S2C_WAITFORSTART = 2,
	C2S_CHECK = 3,
	S2C_GAMEINFOS = 4,
	S2C_DISCONNECT = 5,
	C2S_INPUT = 6,
	S2C_SNAPSHOT = 7,
};

/*
============= TEXTURE =================
*/

class texture_t
{
public:
	unsigned int textureId;
	int w;
	int h;
	char* name;
};
/*
============== KEY ====================
*/

typedef struct {
	char	*name;
	int		keynum;
} keyname_t;

/*
============= SNAPSHOT ================
*/

class snapshot
{
public:
	snapshot() : countEntity(0), serverTime(0) {};
	dynamic_entity entities[MAX_ENTITIES_IN_SNAPSHOT];
	int countEntity;
	int serverTime;
};



class Client
{
public:
	Client()
	{
		for (int i = 0; i < BACKED_SNAPSHOT; i++)
		{
			snapBacked[i] = snapshot();
		}
	};
	int clientNumber;
	ENetPeer *peer;
	bool authed;
	int id;
	int team;
	character *c;
	int idCharacter;
	int skin;
	int ping;
	snapshot snapBacked[BACKED_SNAPSHOT];
	usercmd lastCmd;
};

#endif
