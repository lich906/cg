#pragma once

#include <string>
#include <memory>

#include "view_model/SpaceObjectView.h"
#include "model/SpaceObject.h"

class SpaceObjectFactory
{
public:
	struct CreationResult
	{
		std::unique_ptr<SpaceObject> object;
		std::unique_ptr<SpaceObjectView> view;
	};

	static CreationResult CreateObjectAndView(const std::string& name, float mass, float scale, const gfx::Texture& texture, const gfx::Vector& initialPosition);
};
