#ifndef __ENGINE_CONSOLE_H
#define __ENGINE_CONSOLE_H

#include "interface.h"

class IConsole : public IInterface
{
public:
	static const char *InterfaceName() { return "console"; }
	
	enum
	{
		PRINT_STANDARD = 0,
		PRINT_ERROR,
		PRINT_DEBUG,
	};
private:
	virtual void AddCommand(const char *pName, int Flags, void* FCommandCallback) = 0;
	virtual void Execute(const char *pStr) = 0;
	virtual void ExecuteFile(const char *pFilename) = 0;
	virtual void Print(int Level, const char *pStr);
};

#endif