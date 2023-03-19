#include "model/SpaceObject.h"

SpaceObjectPtr SpaceObject::Create(std::string name, float mass, Vector initialPos, Vector initialVel)
{
	auto instance = new SpaceObject(std::move(name), mass, std::move(initialPos), std::move(initialVel));
	return std::unique_ptr<SpaceObject>(instance);
}

SpaceObject::SpaceObject(std::string name, float mass, Vector initialPos, Vector initialVel)
	: m_name(std::move(name))
	, m_mass(mass)
	, m_currentPosition(std::move(initialPos))
	, m_currentVelocity(std::move(initialVel))
{
}

void SpaceObject::NextPosition(float dt)
{
	Vector deltaPos = m_currentVelocity * dt;
	m_currentPosition += deltaPos;
	Moved(deltaPos);
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
	Vector deltaPos = p - m_currentPosition;
	m_currentPosition = std::move(p);
}

std::string SpaceObject::GetName() const
{
	return m_name;
}
