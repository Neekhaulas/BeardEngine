
#ifndef __SHARED_H
#define __SHARED_H

#ifndef __GNUC__
#ifndef __attribute__
#define __attribute__(x)
#endif
#endif

#define PRODUCT_NAME "BeardEngine"
#define VERSION "0.01"

#define MASTERSERVER "be.grandebar.be"
#define PORT_SERVER_DEFAULT 21430

#define CLIENT_WINDOW_TITLE "BeardEngine Protoype"

#define MAX_EVENTS_QUEUED 256

typedef enum { bfalse, btrue } beboolean;

/*
============= VECTOR ===============
*/

typedef float vec;
typedef vec vec2[2];

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

typedef struct _entityState entityState;

typedef enum
{
	ET_GENERAL,
	ET_PLAYER,
	ET_ITEM,
	ET_PROJECTILE,
	ET_BEAM
} entityType;

struct _entityState
{
	int id;
	int entityType;

	vec2 pos;
	
	vec2 origin;
	vec2 origin2;
};

/*
============== SNAPSHOT ===========
*/

#define MAX_ENTITIES_PER_SNAPSHOT 64

typedef struct {
	int ping;

	int serverTime;

	int numEntities;
	entityState entities[MAX_ENTITIES_PER_SNAPSHOT];
} snapshot;


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

#endif
