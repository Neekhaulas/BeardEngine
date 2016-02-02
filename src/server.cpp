#include "common.h"

#ifdef SERVER
#include <vector>
#include <ctime>
#include "packets.h"

ENetHost *serverHost = NULL;
Client* clients[TOTAL_PLAYERS];
int countClients(0);
int map(0);
bool waitingPlayers;
int actualTime(0);
int lastTime(0);

Cvar* dedicated;
Cvar* version;
Cvar* developper;
Cvar* s_masterserver;
Cvar* g_gravity;
Cvar* sv_distance_snapshot;
Cvar* sv_snap_rate;

int Server_Count_Client()
{
	return TOTAL_PLAYERS;
}

Client* Server_Get_Client(int client)
{
	return clients[client];
}

void Server_Push_Snapshot(Client *client, snapshot *s)
{
	for (int i = BACKED_SNAPSHOT - 2; i > 0; i--)
	{
		client->snapBacked[i] = client->snapBacked[i + 1];
	}
	memcpy(&client->snapBacked[BACKED_SNAPSHOT - 1], s, sizeof(snapshot));
}

void Server_Delta_Snapshot(Client *client, snapshot *s)
{

}

void Server_Make_Snapshot(Client *client, int actualTime)
{
	snapshot *s;
	s = new snapshot();
	s->serverTime = actualTime;
	for (int i = 0; i < Game_Get_Entities().size(); i++)
	{
		if (Entity_Distance(client->character, Game_Get_Entities().at(i)) <= sv_distance_snapshot->valuef)
		{
			if (s->countEntity < MAX_ENTITIES_IN_SNAPSHOT)
			{
				memcpy(&s->entities[s->countEntity++], Game_Get_Entities().at(i), sizeof(entity));
			}
		}
	}
	PacketSnapshot pkt = PacketSnapshot();
	memcpy(&pkt.snapshot, s, sizeof(snapshot));
	Server_Send_To(client->peer, reinterpret_cast<uint8*>(&pkt), sizeof(PacketSnapshot), CHL_S2C, ENET_PACKET_FLAG_RELIABLE);
	Server_Push_Snapshot(client, s);
	delete s;
}

bool is_in_game(int idUser)
{
	for (int i = 0; i < TOTAL_PLAYERS; i++)
	{
		if (clients[i] != NULL)
		{
			if (clients[i]->id == idUser)
			{
				return true;
			}
		}
	}
	return false;
}

int put_player_in_team()
{
	int team1(0), team2(0);

	for (int i = 0; i < TOTAL_PLAYERS; i++)
	{
		if (clients[i] != NULL)
		{
			if (clients[i]->team == 1)
			{
				team1++;
			}
			else if (clients[i]->team == 2)
			{
				team2++;
			}
		}
	}

	if (team1 < team2)
	{
		return 1;
	}
	else if (team1 > team2)
	{
		return 2;
	}
	else
	{
		return 0;
	}
}

void fatal_error(char* error)
{
	printf(error);
	Server_Cleanup();
	exit(EXIT_FAILURE);
}

void Server_Send_Game_State()
{
	if (!Game_Is_Started())
		return;
	for (int i = 0; i < TOTAL_PLAYERS; i++)
	{
		if (clients[i] != NULL)
		{
			bool needSnap(false);
			if (clients[i]->snapBacked[BACKED_SNAPSHOT - 1].serverTime + sv_snap_rate->value < actualTime)
			{
				needSnap = true;
			}
			if (needSnap)
			{
				Server_Make_Snapshot(clients[i], actualTime);
			}
		}
	}
}

Client* add_client()
{
	Client* c = NULL;
	for (int i = 0; i < TOTAL_PLAYERS; i++)
	{
		if (clients[i] == NULL)
		{
			c = new Client;
			c->clientNumber = i;
			c->authed = false;
			c->team = 0;
			clients[i] = c;
			return c;
		}
	}
	return NULL;
}

void Server_Disconnect_Player(int clientNumber, int reason)
{
	Client c = *clients[clientNumber];
	enet_peer_disconnect(c.peer, reason);
}

void Server_Send_To(ENetPeer* peer, const uint8 *source, uint32 length, uint8 channelNo, uint32 flag)
{
	if (peer == NULL)
		return;
	uint8* data = new uint8[length];
	memcpy(data, source, length);

	ENetPacket *packet = enet_packet_create(data, length, flag);
	if (enet_peer_send(peer, channelNo, packet) < 0)
	{
		delete[] data;
		delete packet;
		Print_Error(1, "[NETWORK]Error while sending packet...");
		return;
	}

	delete[] data;
}

void Server_Send_Infos(int clientNumber)
{
	PacketHeader packet(1);
	Server_Send_To(clients[clientNumber]->peer, reinterpret_cast<uint8 *>(&packet), sizeof(packet), CHL_S2C, ENET_PACKET_FLAG_RELIABLE);
}

void Server_Frame()
{
	ENetEvent event;
	bool eventProcessed = false;
	while (!eventProcessed)
	{
		if (enet_host_check_events(serverHost, &event) <= 0)
		{
			if (enet_host_service(serverHost, &event, 5) <= 0)
				break;
			eventProcessed = true;
		}
		switch (event.type)
		{
			case ENET_EVENT_TYPE_CONNECT:
			{
				Print("Client connected, waiting for informations");
				break;
			}

			case ENET_EVENT_TYPE_RECEIVE:
			{
				Server_Handle_Packet(event.packet, event.peer, (int)event.peer->data, event.channelID);
				break;
			}

			case ENET_EVENT_TYPE_DISCONNECT:
			{
				Print("Event : disconnect");
				enet_peer_disconnect(event.peer, 0);
				clients[(int)event.peer->data] = NULL;
				break;
			}

			default:
				break;
		}
	}
	Server_Send_Game_State();
}

void Server_Send_Game_Infos(ENetPeer* peer, int team)
{
	PacketSendGameInfos pkt = PacketSendGameInfos();
	pkt.map = map;
	pkt.team = team;
	Server_Send_To(peer, reinterpret_cast<uint8*>(&pkt), sizeof(PacketSendGameInfos), CHL_S2C, ENET_PACKET_FLAG_RELIABLE);
}

void Server_Send_Waiting_For_Start(ENetPeer* peer)
{
	PacketWaitingForStart pkt = PacketWaitingForStart();
	Server_Send_To(peer, reinterpret_cast<uint8*>(&pkt), sizeof(PacketWaitingForStart), CHL_S2C, ENET_PACKET_FLAG_RELIABLE);
}

void Server_Handle_Packet(ENetPacket* packet, ENetPeer* peer, int client, int chan)
{
	PacketHeader *header = reinterpret_cast<PacketHeader*>(packet->data);

	switch(header->cmd)
	{
	case C2S_CHECK:
	{
		PacketChecking *pkt = reinterpret_cast<PacketChecking*>(packet->data);
		if (pkt->version != VERSION)
		{
			Print("Wrong version");
			Server_Disconnect_Player(client, DISCONNECT_WRONG_VERSION);
			//Send packet wrong version
		}

		if (waitingPlayers)
		{
			if (is_in_game(pkt->idUser))
			{
				Print("Already in game");
				Server_Disconnect_Player(client, DISCONNECT);
				//Send packet already in game
			}

			Client* c = add_client();
			if (c == NULL)
			{
				Print("Can't accept anymore connection");
				enet_peer_disconnect(peer, DISCONNECT_MAXCLIENTS);
				break;
			}
			c->peer = peer;
			c->peer->data = (void*)c->clientNumber;
			c->id = pkt->idUser;
			c->authed = true;
			c->team = put_player_in_team();
			if (c->team == 0)
			{
				c->team = 1;
			}

			Server_Send_Game_Infos(peer, c->team);
			Server_Send_Waiting_For_Start(peer);

			/* Send informations :
			- Map
			- Team
			- How much players
			*/
			Game_Start();
		}
		delete pkt;
	}
		break;

	case C2S_INPUT:
	{
		PacketInput *pkt = reinterpret_cast<PacketInput*>(packet->data);
		clients[client]->lastCmd = usercmd(pkt->lerp, pkt->horizontalMove, pkt->angle, pkt->button);
		delete pkt;
	}
	break;

	default:
		Print("Cannot handle packet from %d on chan %d with cmd %d", client, chan, header->cmd);
		break;
	}
}

bool Server_Init(int argc, char** argv)
{
	/*
	Parser les arguments
	*/
	char* date = __DATE__;
	char* version_str = (char*)malloc(strlen(PRODUCT_NAME " client 1 (%s)") + 1);
	
	dedicated = Cvar_Set("dedicated", "1", CVAR_READ_ONLY, "If this is dedicated server");

	developper = Cvar_Set("developer", "1", CVAR_READ_ONLY, "If the developper mod is on");
	g_gravity = Cvar_Set("g_gravity", "800", CVAR_CHEATS, "Gravity of the game");

	sv_distance_snapshot = Cvar_Set("sv_distance_snapshot", "100", CVAR_PROTECTED, "Distance to add entities in the snapshot");
	sv_snap_rate = Cvar_Set("sv_snap_rate", "20", CVAR_PROTECTED, "Number of snapshot to send every second");

	Command_Exec("exec server.cfg");

	ENetAddress address;
	address.host = ENET_HOST_ANY;
	address.port = PORT_SERVER_DEFAULT;

	serverHost = enet_host_create(&address, TOTAL_PLAYERS, 3, 0, 0);
	if (!serverHost)
	{
		fatal_error("cannot start the server");
	}

	atexit(enet_deinitialize);
	atexit(Server_Cleanup);
	enet_time_set(0);

	Game_Init();
	Game_Load_Map("bearmap.bem");

	waitingPlayers = true;

	std::clock_t start = std::clock();

	for (;;)
	{
		actualTime = std::clock() - start;
		//Console_Frame();
		Game_Frame(0, 0);
		Server_Frame();
		Game_Frame(actualTime, lastTime);

		lastTime = actualTime;
	}
		
	return true;
}

void Server_Cleanup(void)
{
	enet_host_destroy(serverHost);
}

void Server_Think()
{

}

int main(int argc, char** argv)
{
	/*
	Set mode
	Load map
	Wait for everyone
	Wait for pick
	Start
	*/
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