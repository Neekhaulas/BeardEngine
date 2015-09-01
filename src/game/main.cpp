
#include <engine/interface.h>
#include <engine/console.h>
#include "client.h"

int main(int argc, const char **argv)
{
	IClient *pClient = CreateClient();
	ICore *pCore = ICore::CreateCore();
	
	pCore->RegisterInterface(pClient);
	
	IConsole *pConsole = IConsole::CreateConsole();
	
	pClient->Run();
	
	return 0;
}