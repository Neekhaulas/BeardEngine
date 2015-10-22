#include "common.h"
#include "shared.h"
#include <enet/enet.h>

int Network_Init()
{
	if (enet_initialize() != 0)
	{
		fprintf(stderr, "An error occurred while initializing ENet.\n");
		return 1;
	}
	atexit(enet_deinitialize);
}