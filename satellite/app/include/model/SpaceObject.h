#pragma once

#include <memory>
#include <string>

#include "boost/signals2.hpp"

#include "graphics/Vector.h"

using VectorSlotType = boost::signals2::signal<void(const gfx::Vector&)>::slot_type;

class SpaceObject
{
public:

	/*
		Create unique SpaceObject instance.
	*/
	static std::unique_ptr<SpaceObject> Create(const std::string& name, float size,
		float mass, const gfx::Vector& initialPos,
		const gfx::Vector& initialVelocity = gfx::Vector());

	/*
		Sets Space Object's position according given acceleration after 'dt' time

		and invoke Moved() method to trigger corresponding Space Object View notification
	*/
	void NextPosition(const gfx::Vector& acceleration, float dt);

	gfx::Vector GetCurrentPosition() const;
	float GetMass() const;
	gfx::Vector GetCurrentVelocity() const;
	std::string GetName() const;

	void SetCurrentPosition(const gfx::Vector& p);
	void SetCurrentVelocity(const gfx::Vector& v);

	bool ExistsAtPos(const gfx::Vector& pos) const;

	boost::signals2::connection RegisterPositionObs(const VectorSlotType& slot, bool instantNotify = false);
	boost::signals2::connection RegisterVelocityObs(const VectorSlotType& slot, bool instantNotify = false);

private:
	SpaceObject(const std::string& name, float mass, float size,
		const gfx::Vector& initialPos, const gfx::Vector& initialVelocity = gfx::Vector());

	std::string m_name;
	float m_mass, m_size;
	gfx::Vector m_velocity, m_position;

	boost::signals2::signal<void(const gfx::Vector&)> m_positionSignal, m_velocitySignal;
};
