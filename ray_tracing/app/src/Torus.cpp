#include <cmath>
#include "Torus.h"
#include "../vendor/Quartic/quartic.h"

Torus::Torus(float R, float r)
	: m_R(R)
	, m_r(r)
{
}

std::optional<float> Torus::FindLowestHitTime(const Ray& ray) const
{
	glm::vec3 origin = ray.Origin + ray.Direction * 5.0f * TIME_EPSILON;

	const float squareDir = glm::dot(ray.Direction, ray.Direction);
	const float squareOrigin = glm::dot(origin, origin);
	const float dirOriginDot = glm::dot(ray.Direction, origin);
	const float squareRadiusesSum = m_R * m_R + m_r * m_r;

	const float a = std::powf(squareDir, 2.0f);
	const float b = 4 * squareDir * dirOriginDot;
	const float c = 2 * squareDir * (squareOrigin - squareRadiusesSum) + 4 * std::powf(dirOriginDot, 2.0f) + std::powf(2 * m_R * ray.Direction.y, 2.0f);
	const float d = 4 * (squareOrigin - squareRadiusesSum) * dirOriginDot + 8 * m_R * m_R * origin.y * ray.Direction.y;
	const float e = std::powf(squareOrigin - squareRadiusesSum, 2.0f) - 4 * m_R * m_R * (m_r * m_r - origin.y * origin.y);

	auto roots = solve_quartic(b / a, c / a, d / a, e / a);

	std::optional<float> time;
	/* Find lowest positive real root */
	for (size_t i = 0; i < roots.size(); ++i)
	{
		float im = (float)roots[i].imag();
		float re = (float)roots[i].real();
		if (fpclassify(im) == FP_ZERO && re > 0.0f && (!time || re < *time))
		{
			time = re;
		}
	}

	return time;
}

glm::vec3 Torus::GetNormalInLocalSpace(const glm::vec3& point) const
{
	float squareRadiusesSum = m_R * m_R + m_r * m_r;

	float pSquared = glm::dot(point, point);

	glm::vec3 n = glm::vec3(
		4.0 * point.x * (pSquared - squareRadiusesSum),
		4.0 * point.y * (pSquared - squareRadiusesSum + 2.0 * m_R * m_R),
		4.0 * point.z * (pSquared - squareRadiusesSum));

	return n;
}
