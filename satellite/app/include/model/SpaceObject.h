#pragma once

#include <memory>
#include <string>

#include "signal/aliases.h"

class SpaceObject
{
public:

	~SpaceObject();

	/*
		Create unique SpaceObject instance.
	*/
	static std::unique_ptr<SpaceObject> Create(const std::string& name, float size,
		float mass, const glm::vec2& initialPos,
		const glm::vec2& initialVelocity = glm::vec2());

	void NextVelocity(const glm::vec2& acceleration, float dt);
	void NextPosition(float dt);

	glm::vec2 GetCurrentPosition() const;
	float GetRadius() const;
	float GetMass() const;
	glm::vec2 GetCurrentVelocity() const;
	std::string GetName() const;

	void SetCurrentPosition(const glm::vec2& p);
	void SetCurrentVelocity(const glm::vec2& v);

	bool ExistsAtPos(const glm::vec2& pos) const;

	Connection RegisterPositionObs(const VectorSignal::slot_type& slot, bool instantNotify = false);
	Connection RegisterVelocityObs(const VectorSignal::slot_type& slot, bool instantNotify = false);
	Connection RegisterDeletionObs(const VoidSignal::slot_type& slot);

private:
	SpaceObject(const std::string& name, float mass, float size,
		const glm::vec2& initialPos, const glm::vec2& initialVelocity = glm::vec2());

	std::string m_name;
	float m_mass, m_size;
	glm::vec2 m_velocity, m_position;

	VectorSignal m_positionSignal, m_velocitySignal;
	VoidSignal m_deletionSignal;
};
