#include "common.h"
#include "client.h"
#include "client_input.h"
#include "packets.h"

#ifndef DEDICATED

ENetHost *hostClient = NULL;
ENetPeer *peerClient = NULL;
int connectionAttemps = 0;
unsigned int timeoutTimer = 0;
beboolean connecting = bfalse, connected = bfalse;


void Client_Init()
{
	if (enet_initialize() != 0)
	{
		Print_Error(1, "Cannot start enet");
		exit(1);
	}

	Command_Add("connect", Client_Connect_f);

	atexit(Client_Cleanup);
	atexit(enet_deinitialize);

	Client_Init_Input();
	Print("client initialized");
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
		connecting = btrue;
		connectionAttemps = 0;
		timeoutTimer = SDL_GetTicks() + 3000;
		Print("Trying to connect to %s:%d", serverAddress, port);
	}
	else
	{
		Print_Error(1, "Cannot connect to the server");
	}
}

void Client_Abort_Connection()
{
	if (!peerClient)
		return;
	if (peerClient->state != ENET_PEER_STATE_DISCONNECTED)
		enet_peer_reset(peerClient);
	peerClient = NULL;
	connecting = bfalse;
}

void Client_S2C()
{
	if (!hostClient || (!connecting && !peerClient))
		return;
	if (connecting && timeoutTimer < SDL_GetTicks())
	{
		Print("Retrying to connect...");
		timeoutTimer = SDL_GetTicks() + 3000;
		connectionAttemps++;
		if (connectionAttemps > 3)
		{
			Print("Cannot connect to the server");
			Client_Abort_Connection();
			return;
		}
	}

	ENetEvent event;

	while (enet_host_service(hostClient, &event, 0) > 0)
	{
		switch (event.type)
		{
		case ENET_EVENT_TYPE_CONNECT:
			connecting = bfalse;
			connected = btrue;
			Print("Connected");
			break;
		case ENET_EVENT_TYPE_RECEIVE:
			Client_Handle_Packet(event.channelID, event.packet);
			//enet_packet_destroy(event.packet);
			break;

		case ENET_EVENT_TYPE_DISCONNECT:
			printf("%s disconnected.\n", event.peer->data);
			/* Reset the peer's client information. */
			event.peer->data = NULL;
		}
	}
}

void Client_Handle_Packet(enet_uint8 chanel, ENetPacket* packet)
{
	PacketHeader *header = reinterpret_cast<PacketHeader*>(packet->data);
	Print("Packet received on chanel %d with packet id %d", chanel, header->cmd);
}

void Client_Disconnect()
{
	if (peerClient)
	{
		enet_peer_disconnect(peerClient, DISCONNECT);
		enet_host_flush(hostClient);
		enet_peer_reset(peerClient);
	}
}

void Client_Cleanup()
{
	Client_Abort_Connection();
	Client_Disconnect();
	if (hostClient)
	{
		enet_host_destroy(hostClient);
		hostClient = NULL;
	}
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