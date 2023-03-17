#pragma once

#include "glad_glfw.h"

struct Vector
{

	static constexpr GLint Size = 2;

	constexpr Vector(float x_ = 0.0f, float y_ = 0.0f);
	
	/*
		Check that vector is non zero vector.
	*/
	operator bool() const;

	Vector& operator+=(const Vector& rhs);
	Vector& operator*=(float scalar);
	Vector& operator+=(float scalar);

	bool operator>=(const Vector& rhs) const;
	bool operator<=(const Vector& rhs) const;
	bool operator>(const Vector& rhs) const;
	bool operator<(const Vector& rhs) const;
	
	bool operator!=(const Vector& rhs) const;
	bool operator==(const Vector& rhs) const;

	GLfloat x, y;
};

Vector operator+(const Vector& lhs, const Vector& rhs);
Vector operator-(const Vector& v);
Vector operator-(const Vector& lhs, const Vector& rhs);
Vector operator*(const Vector& v, float scalar);
