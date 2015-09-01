#ifndef __ENGINE_CVAR_H
#define __ENGINE_CVAR_H

#include "interface.h"

class IVariable : public IInterface
{
public:
	static const char *InterfaceName() { return "variable"; }
}

#endif