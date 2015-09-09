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
			Print("Scancode: 0x%02x(%s) Sym: 0x%02x(%s)",
				e.key.keysym.scancode, SDL_GetScancodeName(e.key.keysym.scancode),
				e.key.keysym.sym, SDL_GetKeyName(e.key.keysym.sym));
			break;

		case SDL_QUIT:
			Command_Exec("quit");
			break;
		}
	}
#endif
}