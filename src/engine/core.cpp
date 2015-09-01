#include <iostream>
#include <stdio.h>
#include <string.h>

#include "system.h"
#include "core.h"

class CCore : public ICore
{
private:
	class InterfaceInfo
	{
	public:
		char m_aName[64];
		IInterface *m_pInterface;
		InterfaceInfo()
		{
			m_aName[0] = 0;
			m_pInterface = 0;
		}
	};
	int m_CountInterface;
	InterfaceInfo m_aInterfaces[MAX_INTERFACES];
	
	InterfaceInfo *FindInterface(const char* pName)
	{
		for(int i = 0; i < m_CountInterface; i++)
		{
			if(strcmp(pName, m_aInterfaces[i].m_aName) == 0)
			{
				return &m_aInterfaces[i];
			}
		}
		return 0;
	}
public:
	CCore()
	{
		m_CountInterface = 0;
	};
	
	virtual bool RegisterInterfaceImpl(const char *pName, IInterface *pInterface)
	{
		if(FindInterface(pName) != 0)
		{
			std::cerr << "Error while registering interface, can't register interface twice" << std::endl;
			return false;
		}
		
		pInterface->m_pCore = this;
		m_aInterfaces[m_CountInterface].m_pInterface = pInterface;
		strcpy(m_aInterfaces[m_CountInterface].m_aName, pName);
		m_CountInterface++;
		
		return true;
	}

	virtual bool ReregisterInterfaceImpl(const char *pName, IInterface *pInterface)
	{


		return true;
	}

	virtual IInterface *RequestInterfaceImpl(const char *pName)
	{
		return 0;
	}
};

ICore *ICore::CreateCore() { return new CCore(); }