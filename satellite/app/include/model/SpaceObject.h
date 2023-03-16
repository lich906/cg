#pragma once

#include "glad_glfw.h"

#include "types/Vector.h"
#include "ObservableSpaceObject.h"

struct UniqueId
{
	UniqueId()
		: m_id{ std::hash<double>{}(glfwGetTime()) } {}

	operator size_t() const { return m_id; }

private:
	size_t m_id;
};

class SpaceObject : public ObservableSpaceObject
{
public:
	SpaceObject(float mass, Vector initialPos, Vector initialVelocity);

	void NextPosition(float dt);

	// Inherited via IObservableSpaceObject
	Vector GetCurrentPosition() const override;

	size_t GetId() const;
	float GetMass() const;
	Vector GetCurrentVelocity() const;

	void SetCurrentPosition(Vector p);
	void SetCurrentVelocity(Vector v);

private:
	UniqueId m_id;

	float m_mass;
	Vector m_currentVelocity;
	Vector m_currentPosition;
};
