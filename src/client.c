#include "common.h"
#include "client.h"
#include "client_input.h"

#ifndef DEDICATED

static SDL_Window *window = NULL;

ENetHost *hostClient = NULL;
ENetPeer *peerClient = NULL;
int connectionAttemps = 0;
int timeoutTimer = 0;

void Client_Init()
{
	Print("Window initializing");
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		Print_Error(1, "Can't initialize SDL Video");
		exit(1);
	}

	window = SDL_CreateWindow(CLIENT_WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	if (!window)
	{
		Print_Error(1, "Can't create SDL window");
		exit(1);
	}

	if (enet_initialize() != 0)
	{
		Print_Error(1, "Cannot start enet");
		exit(1);
	}

	Command_Add("connect", Client_Connect_f);

	atexit(Client_Cleanup);
	atexit(enet_deinitialize);

	Client_Init_Input();
}

void Client_Connect(const char* serverAddress, int port)
{
	if (port <= 0)
	{
		port = PORT_SERVER_DEFAULT;
	}
	
	ENetAddress address;
	address.port = port;

	if (!serverAddress)
		return;
	enet_address_set_host(&address, serverAddress);

	if (!hostClient)
		hostClient = enet_host_create(NULL, 2, 3, 0, 0);

	if (hostClient)
	{
		peerClient = enet_host_connect(hostClient, &address, 3, 0);
		enet_host_flush(hostClient);
		Print("Trying to connect to %s:%d", serverAddress, port);
	}
	else
	{
		Print_Error(1, "Cannot connect to the server");
	}
}

void Client_S2C()
{
	ENetEvent event;
	/* Wait up to 1000 milliseconds for an event. */
	while (enet_host_service(hostClient, &event, 1000) > 0)
	{
		switch (event.type)
		{
		case ENET_EVENT_TYPE_CONNECT:
			printf("A new client connected from %x:%u.\n",
				event.peer->address.host,
				event.peer->address.port);
			/* Store any relevant client information here. */
			event.peer->data = "Client information";
			break;
		case ENET_EVENT_TYPE_RECEIVE:
			printf("A packet of length %u containing %s was received from %s on channel %u.\n",
				event.packet->dataLength,
				event.packet->data,
				event.peer->data,
				event.channelID);
			/* Clean up the packet now that we're done using it. */
			enet_packet_destroy(event.packet);

			break;

		case ENET_EVENT_TYPE_DISCONNECT:
			printf("%s disconnected.\n", event.peer->data);
			/* Reset the peer's client information. */
			event.peer->data = NULL;
		}
	}
}

void Client_Cleanup()
{
	enet_host_destroy(hostClient);
}

void Client_Connect_f()
{
	if (Command_Argc() == 1)
	{
		Print("usage : connect <host> [port]");
		return;
	}
	else if (Command_Argc() == 2)
	{
		Client_Connect(Command_Argv(1), 0);
	}
	else if (Command_Argc() >= 3)
	{
		Client_Connect(Command_Argv(1), atoi(Command_Argv(2)));
	}
}

#endif