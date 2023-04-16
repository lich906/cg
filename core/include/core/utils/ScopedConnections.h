#pragma once

#include "corepch.h"

namespace core::utils
{

using ScopedConnection = boost::signals2::scoped_connection;

class ScopedConnections
{
public:
	ScopedConnections();
	ScopedConnections(std::vector<ScopedConnection>&& connectionsVect);

	ScopedConnections& operator+=(ScopedConnection&& connection);

private:
	std::vector<ScopedConnection> m_connections;
};

} // namespace core::utils
