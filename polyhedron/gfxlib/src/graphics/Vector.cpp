#include "gfxpch.h"

#include "graphics/Vector.h"

namespace gfx
{

Vector::Vector()
	: x(0.0f)
	, y(0.0f)
	, z(0.0f)
{
}

constexpr Vector::Vector(float x_, float y_, float z_)
	: x(x_)
	, y(y_)
	, z(z_)
{
}

Vector::operator bool() const
{
	return x != 0.0f || y != 0.0f || z != 0.0f;
}

float Vector::Mod() const
{
	return sqrtf(SquareMod());
}

float Vector::SquareMod() const
{
	return x * x + y * y;
}

Vector Vector::Unit() const
{
	return *this / Mod();
}

Vector& Vector::operator+=(const Vector& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Vector& Vector::operator-=(const Vector& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

Vector& Vector::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

Vector& Vector::operator+=(float scalar)
{
	x += scalar;
	y += scalar;
	z += scalar;
	return *this;
}

bool Vector::operator>=(const Vector& rhs) const
{
	return rhs.x >= x && rhs.y >= y && rhs.z >= z;
}

bool Vector::operator<=(const Vector& rhs) const
{
	return x <= rhs.x && y <= rhs.y && z <= rhs.z;
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
	return x != rhs.x || y != rhs.y || z != rhs.z;
}

bool Vector::operator==(const Vector& rhs) const
{
	return !(*this != rhs);
}

Vector operator+(const Vector& lhs, const Vector& rhs)
{
	return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
}

Vector operator-(const Vector& v)
{
	return { -v.x, -v.y, -v.z };
}

Vector operator-(const Vector& lhs, const Vector& rhs)
{
	return lhs + -rhs;
}

Vector operator*(const Vector& v, float scalar)
{
	return { v.x * scalar, v.y * scalar, v.z * scalar };
}

Vector operator/(const Vector& v, float scalar)
{
	return { v.x / scalar, v.y / scalar, v.z / scalar };
}

} // namespace gfx
