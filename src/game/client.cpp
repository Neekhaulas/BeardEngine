#include "client.h"

CClient::CClient()
{
	
}

IClient *CreateClient()
{
	return new CClient;
}