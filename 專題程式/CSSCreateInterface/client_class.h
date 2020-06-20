#pragma once
#include "dt_recv.h"
class ClientClass
{
public:
	void*		m_pCreateFn;
	void*		m_pCreateEventFn;	// Only called for event objects.
	const char* m_pNetworkName;
	RecvTable*	m_pRecvTable;
	ClientClass* m_pNext;
	int						m_ClassID;	// Managed by the engine.
};
