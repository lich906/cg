#include "factory/SpaceObjectFactory.h"

SpaceObjectFactory::CreationResult SpaceObjectFactory::CreateObjectAndView(const std::string& name, float mass, float scale, const gfx::Texture& texture, const gfx::Vector& initialPosition)
{
	auto object = SpaceObject::Create(name, mass, scale, initialPosition);
	auto objectView = SpaceObjectView::Create(initialPosition, scale, texture);
	objectView->Observe(*object);

	return { std::move(object), std::move(objectView) };
}
