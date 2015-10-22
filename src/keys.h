
#ifndef __KEYS_H
#define __KEYS_H

#include "shared.h"

#define MAX_KEYS 512

typedef enum _keycode
{
	K_NULL = 0,

} keycode;

typedef struct _key
{
	beboolean pressed;
	char* binding;
} key;

int Keys_StringToKeyNum(char *str);
void Keys_Bind_f();

beboolean Keys_IsDown(int keynum);

char* Keys_GetBinding(int keynum);

#endif