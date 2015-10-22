#include "common.h"

ENetHost *serverHost = NULL;

#ifdef SERVER

void fatal_error(char* error)
{
	printf(error);
	Server_Cleanup();
	exit(EXIT_FAILURE);
}

void Server_Send_Game_State()
{

}

void Server_Frame()
{
	ENetEvent event;
	beboolean eventProcessed = bfalse;
	while (!eventProcessed)
	{
		if (enet_host_check_events(serverHost, &event) <= 0)
		{
			if (enet_host_service(serverHost, &event, 5) <= 0)
				break;
			eventProcessed = btrue;
		}
		switch (event.type)
		{
			case ENET_EVENT_TYPE_CONNECT:
			{
				Print("Event : connect");
				break;
			}

			case ENET_EVENT_TYPE_RECEIVE:
			{
				break;
			}

			case ENET_EVENT_TYPE_DISCONNECT:
			{
				break;
			}

			default:
				break;
		}
	}
	Server_Send_Game_State();
}

beboolean Server_Init(int argc, char** argv)
{
	/*
	Parser les arguments
	*/
	char* date = __DATE__;
	char* version_str = malloc(strlen(PRODUCT_NAME " client " VERSION " (%s)") + 1);
	
	dedicated = Cvar_Set("dedicated", "1", CVAR_READ_ONLY, "If this is dedicated server");
	sprintf(version_str, PRODUCT_NAME " dedicated server " VERSION " (%s)", date);
	version = Cvar_Set("version", version_str, CVAR_READ_ONLY, "Version of the client");

	developper = Cvar_Set("developer", "1", CVAR_READ_ONLY, "If the developper mod is on");
	s_masterserver = Cvar_Set("s_masterserver", MASTERSERVER, CVAR_READ_ONLY, "Address of the master server");
	g_gravity = Cvar_Set("g_gravity", "800", CVAR_CHEATS, "Gravity of the game");
	error_reporting = Cvar_Set("error_reporting", "4", CVAR_READ_ONLY, "Level of error");

	ENetAddress address;
	address.host = ENET_HOST_ANY;
	address.port = PORT_SERVER_DEFAULT;

	serverHost = enet_host_create(&address, 6, 3, 0, 0);
	if (!serverHost)
	{
		fatal_error("cannot start the server");
	}

	atexit(enet_deinitialize);
	atexit(Server_Cleanup);
	enet_time_set(0);

	for (;;)
	{
		Server_Frame();
		//Console_Frame();
	}
		
	return btrue;
}

void Server_Cleanup(void)
{
	enet_host_destroy(serverHost);
}

int main(int argc, char** argv)
{
	if (enet_initialize() < 0)
	{
		fatal_error("Error while starting enet");
	}

	Console_Init();
	Cvar_Init();
	Command_Init();

	Server_Init(argc, argv);
}

#endif