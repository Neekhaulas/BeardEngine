#include "client_input.h"
#include "common.h"

void Input_Right_Down(){};

void Client_Init_Input()
{
	Command_Add("+right", Input_Right_Down);
	/*AddCommand("-right", Input_Right_Up);
	AddCommand("+left", Input_Left_Down);
	AddCommand("-left", Input_Left_Up);
	AddCommand("+up", Input_Up_Down);
	AddCommand("-up", Input_Up_Up);
	AddCommand("+down", Input_Down_Down);
	AddCommand("-down", Input_Down_Up);*/

	Command_Add("bind", Keys_Bind_f);
	Command_Add("unbindall", Keys_Unbindall_f);
	Command_Add("bindlist", Keys_Bindlist_f);
}

void Client_Process_Events()
{
#ifndef DEDICATED
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_KEYDOWN:
			Event_Queue(EVT_KEY, (int)e.key.keysym.sym, 1);	
			break;

		case SDL_KEYUP:
			Event_Queue(EVT_KEY, (int)e.key.keysym.sym, 0);
			break;

		case SDL_QUIT:
			Command_Exec("quit");
			break;
		}
	}
#endif
}