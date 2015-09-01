#ifndef __ENGINE_CLIENT_H
#define __ENGINE_CLIENT_H

#include "interface.h"

class IClient : public IInterface
{
protected:
	int m_State;
	
public:
	static const char *InterfaceName() { return "client"; }
	enum
	{
		STATE_DISCONNECTED = 0,
		STATE_TRYING_CONNECTING,
		STATE_DOWNLOADING,
		STATE_PLAYING,
	};
	
	virtual void Connect(const char *pAddress) = 0;
	virtual void Disconnect() = 0;
	virtual void Quit() = 0;
	
	virtual void SendCommand() = 0;
	
	virtual void Run() = 0;
};


extern IClient *CreateClient();

#endif