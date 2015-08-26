
#ifndef __KEYS_H
#define __KEYS_H

#include "shared.h"

#define MAX_KEYS 512

typedef enum
{
	
} keycode;

typedef struct _key
{
	beboolean pressed;
	char* binding;
} key;

int Keys_StringToKeyNum(char *str);
void Keys_Bind_f();
void Keys_Unbindall_f();
void Keys_Bindlist_f();

#endif