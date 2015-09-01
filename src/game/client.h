#ifndef __CLIENT_H
#define __CLIENT_H

#include <engine/client.h>

class CClient : public IClient
{
public:
	CClient();
	void Connect(const char *pAddress){};
	void Disconnect(){};
	void Quit(){};
	
	void SendCommand(){};
	
	void Run(){};
};

#endif