
#ifndef __SHARED_H
#define __SHARED_H

#define PRODUCT_NAME "BeardEngine"
#define VERSION "0.01"

typedef enum { false, true } boolean;

/*
============= CVAR =================
*/

#define CVAR_READ_ONLY 0x00001
#define CVAR_USER_CREATED 0x00002
#define CVAR_CHEATS 0x00004
#define CVAR_PROTECTED 0x00008

typedef struct _Cvar Cvar;

struct _Cvar
{
	char		*name;
	char		*value;
	int			countModified;
	boolean		modified;
	int			flags;

	Cvar		*next;
};

#endif
