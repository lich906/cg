#include "types/Vector.h"

constexpr Vector::Vector(float x_, float y_)
	: x(x_)
	, y(y_)
{
}

Vector::operator bool() const
{
	return x != 0.0f || y != 0.0f;
}

Vector& Vector::operator+=(const Vector& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

Vector& Vector::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

Vector& Vector::operator+=(float scalar)
{
	x += scalar;
	y += scalar;
	return *this;
}

bool Vector::operator>=(const Vector& rhs) const
{
	return rhs.x >= x && rhs.y >= y;
}

bool Vector::operator<=(const Vector& rhs) const
{
	return rhs.x <= x && rhs.y <= y;
}

bool Vector::operator>(const Vector& rhs) const
{
	return !(*this <= rhs);
}

bool Vector::operator<(const Vector& rhs) const
{
	return !(*this >= rhs);
}

bool Vector::operator!=(const Vector& rhs) const
{
	return x != rhs.x || y != rhs.y;
}

bool Vector::operator==(const Vector& rhs) const
{
	return !(*this != rhs);
}

Vector operator+(const Vector& lhs, const Vector& rhs)
{
	return { lhs.x + rhs.x, lhs.y + rhs.y };
}

Vector operator-(const Vector& v)
{
	return { -v.x, -v.y };
}

Vector operator-(const Vector& lhs, const Vector& rhs)
{
	return lhs + -rhs;
}

Vector operator*(const Vector& v, float scalar)
{
	return { v.x * scalar, v.y * scalar };
}
