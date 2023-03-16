#include "model/SpaceObject.h"

SpaceObject::SpaceObject(float mass, Vector initialPos, Vector initialVel)
	: m_mass(mass)
	, m_currentPosition(std::move(initialPos))
	, m_currentVelocity(std::move(initialVel))
{
}

void SpaceObject::NextPosition(float dt)
{
	m_currentPosition.x += m_currentVelocity.x * dt;
	m_currentPosition.y += m_currentVelocity.y * dt;
}

Vector SpaceObject::GetCurrentPosition() const
{
	return m_currentPosition;
}

size_t SpaceObject::GetId() const
{
	return m_id;
}

float SpaceObject::GetMass() const
{
	return m_mass;
}

Vector SpaceObject::GetCurrentVelocity() const
{
	return m_currentVelocity;
}

void SpaceObject::SetCurrentVelocity(Vector v)
{
	m_currentVelocity = std::move(v);
}

void SpaceObject::SetCurrentPosition(Vector p)
{
	m_currentPosition = std::move(p);
}
