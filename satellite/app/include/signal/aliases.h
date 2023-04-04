#pragma once

#include "boost/signals2.hpp"
#include "graphics/Vector.h"

using VectorSignal = boost::signals2::signal<void(const gfx::Vector&)>;
using VoidSignal = boost::signals2::signal<void()>;
using Connection = boost::signals2::connection;
using ScopedConnection = boost::signals2::scoped_connection;
using SpaceObjectSignal = boost::signals2::signal<void(class SpaceObject&)>;
