#include "model/SpaceObject.h"

SpaceObject::~SpaceObject()
{
	m_deletionSignal();
}

std::unique_ptr<SpaceObject> SpaceObject::Create(const std::string& name, float mass, float size, const glm::vec2& initialPos, const glm::vec2& initialVel)
{
	auto instance = new SpaceObject(name, mass, size, initialPos, initialVel);
	return std::unique_ptr<SpaceObject>(instance);
}

SpaceObject::SpaceObject(const std::string& name, float mass, float size, const glm::vec2& initialPos, const glm::vec2& initialVel)
	: m_name(name)
	, m_mass(mass)
	, m_size(size)
	, m_position(initialPos)
	, m_velocity(initialVel)
{
}

void SpaceObject::NextVelocity(const glm::vec2& acceleration, float dt)
{
	m_velocity += acceleration * dt;
	m_velocitySignal(m_velocity);
}

void SpaceObject::NextPosition(float dt)
{
	m_position += m_velocity * dt;
	m_positionSignal(m_position);
}

glm::vec2 SpaceObject::GetCurrentPosition() const
{
	return m_position;
}

float SpaceObject::GetRadius() const
{
	return m_size;
}

float SpaceObject::GetMass() const
{
	return m_mass;
}

glm::vec2 SpaceObject::GetCurrentVelocity() const
{
	return m_velocity;
}

void SpaceObject::SetCurrentVelocity(const glm::vec2& v)
{
	m_velocity = v;
	m_velocitySignal(m_velocity);
}

bool SpaceObject::ExistsAtPos(const glm::vec2& pos) const
{
	glm::vec2 topLeft = m_position - glm::vec2(m_size, m_size);
	glm::vec2 rightBtm = m_position + glm::vec2(m_size, m_size);
	return
		glm::all(glm::lessThanEqual(topLeft, pos)) &&
		glm::all(glm::lessThanEqual(pos, rightBtm));
}

Connection SpaceObject::RegisterPositionObs(const VectorSignal::slot_type& slot, bool instantNotify)
{
	if (instantNotify)
	{
		slot(m_position);
	}

	return m_positionSignal.connect(slot);
}

Connection SpaceObject::RegisterVelocityObs(const VectorSignal::slot_type& slot, bool instantNotify)
{
	if (instantNotify)
	{
		slot(m_velocity);
	}

	return m_velocitySignal.connect(slot);
}

Connection SpaceObject::RegisterDeletionObs(const VoidSignal::slot_type& slot)
{
	return m_deletionSignal.connect(slot);
}

void SpaceObject::SetCurrentPosition(const glm::vec2& p)
{
	m_position = p;
	m_positionSignal(m_position);
}

std::string SpaceObject::GetName() const
{
	return m_name;
}
