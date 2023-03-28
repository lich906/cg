#pragma once

#include <memory>
#include <string>

#include "graphics/Vector.h"
#include "model/ObservableSpaceObject.h"

class SpaceObject : public ObservableSpaceObject
{
public:
	/*
		Create unique SpaceObject instance.
	*/
	static std::unique_ptr<SpaceObject> Create(const std::string& name,
		float mass, const gfx::Vector& initialPos,
		const gfx::Vector& initialVelocity = gfx::Vector());

	/*
		Sets Space Object's position according given acceleration after 'dt' time

		and invoke Moved() method to trigger corresponding Space Object View notification
	*/
	void NextPosition(float acceleration, float dt);

	gfx::Vector GetCurrentPosition() const;
	float GetMass() const;
	gfx::Vector GetCurrentVelocity() const;
	std::string GetName() const;

	/*
		Set Space Object position silently (without Moved() call)
	*/
	void SetCurrentPosition(const gfx::Vector& p);

	void SetCurrentVelocity(const gfx::Vector& v);

private:
	SpaceObject(const std::string& name, float mass,
		const gfx::Vector& initialPos, const gfx::Vector& initialVelocity = gfx::Vector());

	std::string m_name;
	float m_mass;
	gfx::Vector m_currentVelocity;
	gfx::Vector m_currentPosition;
};
