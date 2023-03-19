#pragma once

#include <memory>
#include <string>

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

using SpaceObjectPtr = std::unique_ptr<class SpaceObject>;

class SpaceObject : public ObservableSpaceObject
{
public:
	/*
		Create unique SpaceObject instance.
	*/
	static SpaceObjectPtr Create(std::string name,
		float mass, Vector initialPos, Vector initialVelocity = Vector());

	/*
		Sets Space Object's position after time 'dt'
		and invoke Moved() method to trigger corresponding Space Object View notification
	*/
	void NextPosition(float dt);

	// Inherited via IObservableSpaceObject
	Vector GetCurrentPosition() const override;

	size_t GetId() const;
	float GetMass() const;
	Vector GetCurrentVelocity() const;
	std::string GetName() const;

	/*
		Set Space Object position silently (without Moved() call)
	*/
	void SetCurrentPosition(Vector p);

	void SetCurrentVelocity(Vector v);

private:
	SpaceObject(std::string name, float mass, Vector initialPos, Vector initialVelocity = Vector());

	UniqueId m_id;

	std::string m_name;
	float m_mass;
	Vector m_currentVelocity;
	Vector m_currentPosition;
};
