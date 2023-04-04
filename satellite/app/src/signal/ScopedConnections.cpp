#include "signal/ScopedConnections.h"

ScopedConnections::ScopedConnections()
{
}

ScopedConnections::ScopedConnections(std::vector<ScopedConnection>&& initializerList)
	: m_connections(std::forward<std::vector<ScopedConnection>>(initializerList))
{
}

ScopedConnections& ScopedConnections::operator+=(ScopedConnection&& connection)
{
	m_connections.emplace_back(std::move(connection));
	return *this;
}
