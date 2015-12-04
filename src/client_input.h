#ifndef __CLIENT_INPUT_H
#define __CLIENT_INPUT_H

#include "common.h"

void Client_Init_Input();
void Client_KeyEvent(int key, bool down);
void Client_KeyUpEvent(int key);
void Client_KeyDownEvent(int key);
bool Client_KeyUp(int key);
bool Client_KeyDown(int key);

#endif