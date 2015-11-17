#ifndef __CLIENT_INPUT_H
#define __CLIENT_INPUT_H

#include "common.h"

void Client_Init_Input();
void Client_KeyEvent(int key, beboolean down);
void Client_KeyUpEvent(int key);
void Client_KeyDownEvent(int key);
beboolean Client_KeyUp(int key);
beboolean Client_KeyDown(int key);

#endif