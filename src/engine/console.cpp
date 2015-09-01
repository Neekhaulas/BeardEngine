#include "console.h"

class CConsole : public IConsole
{
public:
	CConsole() {};
private:
	virtual void AddCommand(const char *pName, void* FCommandCallback)
	{
		
	}
	
	virtual void Execute(const char *pStr)
	{
		
	}
	
	virtual void ExecuteFile(const char *pFilename)
	{
		
	}
	
	virtual void Print(int Level, const char *pStr)
	{
		
	}
};

IConsole *IConsole::CreateConsole()
{
	return new CConsole();
}