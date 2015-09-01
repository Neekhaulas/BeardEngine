#ifndef __ENGINE_INTERFACE_H
#define __ENGINE_INTERFACE_H

#include "core.h"

class ICore;
class IInterface;

class IInterface
{
	friend class CCore;
	ICore *m_pCore;
protected:
	ICore *Core() {return m_pCore;}
public:
	IInterface() : m_pCore(0) {}
	virtual ~IInterface() {}
};

#endif