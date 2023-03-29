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

private:
	SpaceObject(const std::string& name, float mass, float size,
		const gfx::Vector& initialPos, const gfx::Vector& initialVelocity = gfx::Vector());

	// Inherited via ObservableSpaceObject
	virtual gfx::Vector GetPosition() const override;
	virtual gfx::Vector GetVelocity() const override;

	std::string m_name;
	float m_mass, m_size;
	gfx::Vector m_currentVelocity, m_currentPosition;
};
