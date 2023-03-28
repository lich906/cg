#include "model/SpaceObject.h"

std::unique_ptr<SpaceObject> SpaceObject::Create(const std::string& name, float mass, const gfx::Vector& initialPos, const gfx::Vector& initialVel)
{
	return std::unique_ptr<SpaceObject>(new SpaceObject(name, mass, initialPos, initialVel));
}

SpaceObject::SpaceObject(const std::string& name, float mass, const gfx::Vector& initialPos, const gfx::Vector& initialVel)
	: m_name(name)
	, m_mass(mass)
	, m_currentPosition(initialPos)
	, m_currentVelocity(initialVel)
{
}

void SpaceObject::NextPosition(float acceleration, float dt)
{
	m_currentVelocity += acceleration * dt;
	VelocityChanged(m_currentVelocity);
	m_currentPosition += m_currentVelocity * acceleration;
	Moved(m_currentPosition);
}

gfx::Vector SpaceObject::GetCurrentPosition() const
{
	return m_currentPosition;
}

float SpaceObject::GetMass() const
{
	return m_mass;
}

gfx::Vector SpaceObject::GetCurrentVelocity() const
{
	return m_currentVelocity;
}

void SpaceObject::SetCurrentVelocity(const gfx::Vector& v)
{
	m_currentVelocity = v;
	VelocityChanged(v);
}

void SpaceObject::SetCurrentPosition(const gfx::Vector& p)
{
	m_currentPosition = p;
}

std::string SpaceObject::GetName() const
{
	return m_name;
}
