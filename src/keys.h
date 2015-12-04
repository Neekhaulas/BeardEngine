
#ifndef __KEYS_H
#define __KEYS_H

#include "shared.h"

#define MAX_KEYS 512

typedef enum
{
	KEY_MOUSE1 = 178,
	KEY_MOUSE2,
	KEY_MOUSE3,
} keyNum_t;

typedef struct _key
{
	bool pressed;
	char* binding;
} key;

int Keys_StringToKeyNum(char *str);
void Keys_Bind_f();

bool Keys_IsDown(int keynum);

char* Keys_GetBinding(int keynum);

#endif