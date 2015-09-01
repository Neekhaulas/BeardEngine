#ifndef __ENGINE_KERNEL_H
#define __ENGINE_KERNEL_H

class ICore;
class IInterface;

#include "interface.h"

class ICore
{
	virtual bool RegisterInterfaceImpl(const char *InterfaceName, IInterface *pInterface) = 0;
	virtual bool ReregisterInterfaceImpl(const char *InterfaceName, IInterface *pInterface) = 0;
	virtual IInterface *RequestInterfaceImpl(const char *InterfaceName) = 0;
public:
	static ICore *CreateCore();
	virtual ~ICore() {}

	// templated access to handle pointer convertions and interface names
	template<class TINTERFACE>
	bool RegisterInterface(TINTERFACE *pInterface)
	{
		return RegisterInterfaceImpl(TINTERFACE::InterfaceName(), pInterface);
	}
	template<class TINTERFACE>
	bool ReregisterInterface(TINTERFACE *pInterface)
	{
		return ReregisterInterfaceImpl(TINTERFACE::InterfaceName(), pInterface);
	}

	// Usage example:
	//		IMyInterface *pMyHandle = Kernel()->RequestInterface<IMyInterface>()
	template<class TINTERFACE>
	TINTERFACE *RequestInterface()
	{
		return reinterpret_cast<TINTERFACE *>(RequestInterfaceImpl(TINTERFACE::InterfaceName()));
	}
};

#endif