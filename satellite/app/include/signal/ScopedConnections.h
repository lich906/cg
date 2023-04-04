#pragma once

#include "aliases.h"

class ScopedConnections
{
public:
	ScopedConnections();
	ScopedConnections(std::vector<ScopedConnection>&& initializerList);

	ScopedConnections& operator+=(ScopedConnection&& connection);

private:
	std::vector<ScopedConnection> m_connections;
};
