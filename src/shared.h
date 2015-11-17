
#ifndef __SHARED_H
#define __SHARED_H

#ifndef __GNUC__
#ifndef __attribute__
#define __attribute__(x)
#endif
#endif

typedef char int8;
typedef short int16;
typedef int int32;
typedef long long int64;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

#define PRODUCT_NAME "BeardEngine"
#define VERSION "0.01"
#define ERROR_LEVEL 1

#define MASTERSERVER "be.grandebar.be"
#define PORT_SERVER_DEFAULT 21430

#define CLIENT_WINDOW_TITLE "BeardEngine Protoype"

#define MAX_EVENTS_QUEUED 256
#define PLAYER_PER_TEAM 1


typedef enum { bfalse, btrue } beboolean;

/*
============= VECTOR ===============
*/
typedef struct _vec vec;

struct _vec { float x, y, z; };

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
	beboolean	modified;
	int			flags;

	Cvar		*next;
	Cvar		*prev;
	int			hashIndex;
};

/*
============== ENTITY =============
*/

typedef enum
{
	ET_GENERAL,
	ET_PLAYER,
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
	int id;
	vec position;
};

class static_entity : public entity
{
	vec size;
	int rotation;
};

class dynamic_entity : public entity
{
public:
	vec velocity;
};

/*
============= OPCODES =================
*/

enum PacketCmd {
	C2S_COMMAND = 1,

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
};


#endif
