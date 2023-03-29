#include "model/SpaceObject.h"

std::unique_ptr<SpaceObject> SpaceObject::Create(const std::string& name, float mass, float size, const gfx::Vector& initialPos, const gfx::Vector& initialVel)
{
	auto instance = new SpaceObject(name, mass, size, initialPos, initialVel);
	return std::unique_ptr<SpaceObject>(instance);
}

SpaceObject::SpaceObject(const std::string& name, float mass, float size, const gfx::Vector& initialPos, const gfx::Vector& initialVel)
	: m_name(name)
	, m_mass(mass)
	, m_size(size)
	, m_currentPosition(initialPos)
	, m_currentVelocity(initialVel)
{
}

gfx::Vector SpaceObject::GetPosition() const
{
	return GetCurrentPosition();
}

gfx::Vector SpaceObject::GetVelocity() const
{
	return GetCurrentVelocity();
}

void SpaceObject::NextPosition(const gfx::Vector& acceleration, float dt)
{
	m_currentVelocity += acceleration * dt;
	VelocityChanged();
	m_currentPosition += m_currentVelocity * dt;
	Moved();
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
	VelocityChanged();
}

bool SpaceObject::ExistsAtPos(const gfx::Vector& pos) const
{
	return
		m_currentPosition - gfx::Vector(m_size, m_size) <= pos &&
		pos <= m_currentPosition + gfx::Vector(m_size, m_size);
}

void SpaceObject::SetCurrentPosition(const gfx::Vector& p)
{
	m_currentPosition = p;
	Moved();
}

std::string SpaceObject::GetName() const
{
	return m_name;
}
