#pragma once

struct Vector
{
	static constexpr unsigned Size = 2;

	constexpr Vector(float x_ = 0.0f, float y_ = 0.0f);

	/*
		Check that vector is non zero vector.
	*/
	operator bool() const;

	/*
		Get length of vector
	*/
	float Mod() const;

	/*
		Get square of length of vector
	*/
	float SquareMod() const;

	/*
		Get unit vector: a vector of length 1 and same direction
	*/
	Vector Unit() const;

	Vector& operator+=(const Vector& rhs);
	Vector& operator*=(float scalar);
	Vector& operator+=(float scalar);

	bool operator>=(const Vector& rhs) const;
	bool operator<=(const Vector& rhs) const;
	bool operator>(const Vector& rhs) const;
	bool operator<(const Vector& rhs) const;

	bool operator!=(const Vector& rhs) const;
	bool operator==(const Vector& rhs) const;

	float x, y;
};

Vector operator+(const Vector& lhs, const Vector& rhs);
Vector operator-(const Vector& v);
Vector operator-(const Vector& lhs, const Vector& rhs);
Vector operator*(const Vector& v, float scalar);
Vector operator/(const Vector& v, float scalar);
