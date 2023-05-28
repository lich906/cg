#pragma once

#include "boost/signals2.hpp"
#include <glm/glm.hpp>

using VectorSignal = boost::signals2::signal<void(const glm::vec2&)>;
using VoidSignal = boost::signals2::signal<void()>;
using Connection = boost::signals2::connection;
using ScopedConnection = boost::signals2::scoped_connection;
using SpaceObjectSignal = boost::signals2::signal<void(class SpaceObject&)>;
