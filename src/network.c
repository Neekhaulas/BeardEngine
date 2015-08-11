#include "common.h"
#include "shared.h"

#ifdef WIN32
#include <winsock2.h>
#include <ws2spi.h>
#include <ws2tcpip.h>

static WSADATA wsa;
static beboolean networkInitialized = bfalse;
static int networkEnabled = 0;

#else

#endif

static SOCKET	ip_socket = INVALID_SOCKET;
static SOCKET	socks_socket = INVALID_SOCKET;

static Cvar* net_ip;
static Cvar* net_port;

SOCKET Network_Socket(char* net_interface, int port)
{
	SOCKET newsocket;
	struct sockaddr_in address;
	unsigned long _true = 1;
	int i = 1;
	
	Print("Port : %d", port);

	if (net_interface)
	{
		Print("Opening socket on %s:%d", net_ip->string, port);
	}
	else
	{
		Print("Opening socket on 0.0.0.0:%d", port);
	}

	if ((newsocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
	{
		Print("Error while creating socket");
		return newsocket;
	}

	if (ioctlsocket(newsocket, FIONBIO, &_true) == SOCKET_ERROR)
	{
		Print("Error on ioctl");
		closesocket(newsocket);
		return newsocket;
	}

	if (setsockopt(newsocket, SOL_SOCKET, SO_BROADCAST, (char *)&i, sizeof(i)) == SOCKET_ERROR)
	{
		Print("Error on setsockopt");
		return newsocket;
	}

	if (!net_interface || !net_interface[0])
	{
		address.sin_family = AF_INET;
		address.sin_addr.S_un.S_addr = INADDR_ANY;
	}
	else
	{
		address.sin_addr.s_addr = inet_addr(net_interface);
		address.sin_family = AF_INET;
	}
	
	address.sin_port = htons((short)port);

	if (bind(newsocket, (void *)&address, sizeof(address)) == SOCKET_ERROR) {
		Print("Error on bind");
		closesocket(newsocket);
		return INVALID_SOCKET;
	}

	return newsocket;
}

void Network_OpenIP()
{
	int port;
	int i;

	port = net_port->value;

	for (i = 0; i < 10; i++)
	{
		ip_socket = Network_Socket(net_ip->string, port + i);

		if (ip_socket != INVALID_SOCKET)
		{
			Cvar_Set2("net_port", Format("%d", port + i), CVAR_LOCKED);
			Print("ip address binded");
			break;
		}
	}
}

void Network_GetCvar()
{
	net_ip = Cvar_Set2("net_ip", "0.0.0.0", CVAR_LOCKED);

	net_port = Cvar_Set2("net_port", Format("%d", PORT_SERVER), CVAR_LOCKED);

	Command_Exec("net_port");
}

void Network_Config(beboolean enableNetworking)
{
	beboolean	stop;
	beboolean	start;

	Network_GetCvar();

	if (enableNetworking == networkEnabled)
	{
		if (enableNetworking)
		{
			stop = btrue;
			start = btrue;
		}
		else
		{
			stop = bfalse;
			start = bfalse;
		}
	}
	else
	{
		if (networkEnabled)
		{
			stop = btrue;
			start = bfalse;
		}
		else
		{
			stop = bfalse;
			start = btrue;
		}
	}

	if (stop)
	{
		if (ip_socket != INVALID_SOCKET)
		{
			closesocket(ip_socket);
			ip_socket = INVALID_SOCKET;
		}

		if (socks_socket != INVALID_SOCKET) {
			closesocket(socks_socket);
			socks_socket = INVALID_SOCKET;
		}
	}

	if (start)
	{
		Network_OpenIP();
	}
}

void Network_Init()
{
#ifdef WIN32
	Print("Initializing Winsock");
	if (WSAStartup(MAKEWORD(1, 1), &wsa))
	{
		Print("Winsock initialization failed.");
		return;
	}

	networkInitialized = btrue;
	Print("Winsock initialized");
#endif

	Network_Config(btrue);
}