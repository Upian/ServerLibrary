#include "IOCPSessionManager.h"

namespace IOCP
{
	SessionManager::SessionManager()
	{

	}
	SessionManager::~SessionManager()
	{
		m_poolSession.Clear();
	}
}
