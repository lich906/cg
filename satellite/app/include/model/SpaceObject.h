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
		float mass, const gfx::Vector& initialPos,
		const gfx::Vector& initialVelocity = gfx::Vector());

	void NextVelocity(const gfx::Vector& acceleration, float dt);
	void NextPosition(float dt);

	gfx::Vector GetCurrentPosition() const;
	float GetRadius() const;
	float GetMass() const;
	gfx::Vector GetCurrentVelocity() const;
	std::string GetName() const;

	void SetCurrentPosition(const gfx::Vector& p);
	void SetCurrentVelocity(const gfx::Vector& v);

	bool ExistsAtPos(const gfx::Vector& pos) const;

	Connection RegisterPositionObs(const VectorSignal::slot_type& slot, bool instantNotify = false);
	Connection RegisterVelocityObs(const VectorSignal::slot_type& slot, bool instantNotify = false);
	Connection RegisterDeletionObs(const VoidSignal::slot_type& slot);

private:
	SpaceObject(const std::string& name, float mass, float size,
		const gfx::Vector& initialPos, const gfx::Vector& initialVelocity = gfx::Vector());

	std::string m_name;
	float m_mass, m_size;
	gfx::Vector m_velocity, m_position;

	VectorSignal m_positionSignal, m_velocitySignal;
	VoidSignal m_deletionSignal;
};
