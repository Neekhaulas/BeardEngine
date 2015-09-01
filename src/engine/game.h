#ifndef __ENGINE_GAME_H
#define __ENGINE_GAME_H

#include "interface.h"

class IGame : public IInterface
{
public:
	virtual void OnInit() = 0;
	virtual void OnConnected() = 0;
	virtual void OnExit() = 0;
	virtual void OnRender() = 0;
	
	virtual const char* GetVersion() = 0;
	virtual const char* GetNetVersion() = 0;
};

extern IGame *CreateGame();

#endif