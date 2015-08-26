#ifndef __ENGINE_INTERFACE_H
#define __ENGINE_INTERFACE_H

class IKernel;
class IInterface;

class IInterface
{
	friend class CKernel;
	IKernel *m_pKernel;
protected:
	IKernel *Kernel() {return m_pKernel;}
public:
	IInterface() : m_pKernel(0) {}
	virtual ~IInterface() {}
};

class IKernel
{
	virtual bool RegisterInterfaceImpl(const char *InterfaceName, IInterface *pInterface) = 0;
	virtual bool ReregisterInterfaceImpl(const char *InterfaceName, IInterface *pInterface) = 0;
	virtual IInterface *RequestInterfaceImpl(const char *InterfaceName) = 0;
public:
	static IKernel *Create();
	virtual ~IKernel() {}

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