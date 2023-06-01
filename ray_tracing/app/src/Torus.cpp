#include <cmath>
#include "Torus.h"
#include "../vendor/Quartic/quartic.h"

Torus::Torus(float R, float r)
	: m_R(R)
	, m_r(r)
{
}

bool Torus::Hit(const Ray& actualRay, HitPayload& payload) const
{
	Ray ray = actualRay;
	ray.Origin += ray.Direction * 5.0f * TIME_EPSILON;
	ray.Transform(GetInverseTransform());

	float squareDir = glm::dot(ray.Direction, ray.Direction);
	float squareOrigin = glm::dot(ray.Origin, ray.Origin);
	float dirOriginDot = glm::dot(ray.Direction, ray.Origin);
	float squareRadiusesSum = m_R * m_R + m_r * m_r;

	float a = std::powf(squareDir, 2.0f);
	float b = 4 * squareDir * dirOriginDot;
	float c = 2 * squareDir * (squareOrigin - squareRadiusesSum) + 4 * std::powf(dirOriginDot, 2.0f) + std::powf(2 * m_R * ray.Direction.y, 2.0f);
	float d = 4 * (squareOrigin - squareRadiusesSum) * dirOriginDot + 8 * m_R * m_R * ray.Origin.y * ray.Direction.y;
	float e = std::powf(squareOrigin - squareRadiusesSum, 2.0f) - 4 * m_R * m_R * (m_r * m_r - ray.Origin.y * ray.Origin.y);

	DComplex* res = solve_quartic(b / a, c / a, d / a, e / a);

	bool hit = false;
	float time = std::numeric_limits<float>::max();
	/* Find least positive real root */
	for (size_t i = 0; i < 4; ++i)
	{
		float im = (float)res[i].imag();
		float re = (float)res[i].real();
		if (fpclassify(im) == FP_ZERO && re > 0.0f && re < time)
		{
			time = re;
			hit = true;
		}
	}

	/* Requirement of solve_quartic() function code */
	delete[] res;

	if (!hit)
		return false;

	if (time > TIME_EPSILON && time < payload.HitTime)
	{
		payload.HitTime = time;
		payload.WorldNormal = glm::normalize(GetNormalMatrix() * GetNormal(ray.At(time)));
		return true; // New closest hit found
	}

	return false; // Found hit isn't closest
}

glm::vec3 Torus::GetNormal(const glm::vec3& p) const
{
	float squareRadiusesSum = m_R * m_R + m_r * m_r;

	float pSquared = glm::dot(p, p);

	glm::vec3 n = glm::vec3(
		4.0 * p.x * (pSquared - squareRadiusesSum),
		4.0 * p.y * (pSquared - squareRadiusesSum + 2.0 * m_R * m_R),
		4.0 * p.z * (pSquared - squareRadiusesSum));

	return glm::normalize(n);
}
