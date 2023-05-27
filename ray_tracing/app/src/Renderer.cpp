#include <execution>

#include "Renderer.h"
#include "Color.h"

static Color ConvertToColor(const glm::vec4& color)
{
	uint8_t r = (uint8_t)(color.r * 255.0f);
	uint8_t g = (uint8_t)(color.g * 255.0f);
	uint8_t b = (uint8_t)(color.b * 255.0f);
	uint8_t a = (uint8_t)(color.a * 255.0f);

	return Color{ r, g, b, a };
}

void Renderer::OnResize(size_t width, size_t height)
{
	m_colorBuffer.Resize((uint32_t)width, (uint32_t)height);

	m_horizontalIndices.resize(width);
	m_verticalIndices.resize(height);
	for (uint32_t i = 0; i < width; i++)
		m_horizontalIndices[i] = i;
	for (uint32_t i = 0; i < height; i++)
		m_verticalIndices[i] = i;
}

void Renderer::Render(const Scene& scene, const Camera& camera)
{
	m_activeScene = &scene;
	m_activeCamera = &camera;

#define MT 1
#if MT
	std::for_each(std::execution::par, m_verticalIndices.begin(), m_verticalIndices.end(),
		[this](uint32_t y) {
			std::for_each(std::execution::par, m_horizontalIndices.begin(), m_horizontalIndices.end(),
				[this, y](uint32_t x) {
					glm::vec4 color = GetPixelColor(x, y);
					color = glm::clamp(color, glm::vec4(0.0f), glm::vec4(1.0f));
					m_colorBuffer.SetPixelColor(x, y, ConvertToColor(color));
				});
		});
#else
	std::for_each(m_verticalIndices.begin(), m_verticalIndices.end(),
		[this](uint32_t y) {
			std::for_each(m_horizontalIndices.begin(), m_horizontalIndices.end(),
				[this, y](uint32_t x) {
					glm::vec4 color = GetPixelColor(x, y);
					color = glm::clamp(color, glm::vec4(0.0f), glm::vec4(1.0f));
					m_colorBuffer.SetPixelColor(x, y, ConvertToColor(color));
				});
		});
#endif
}

const ColorBuffer& Renderer::GetColorBuffer() const
{
	return m_colorBuffer;
}

glm::vec4 Renderer::GetPixelColor(uint32_t x, uint32_t y) const
{
	Ray ray;
	ray.Origin = m_activeCamera->GetPosition();
	ray.Direction = m_activeCamera->GetRayDirections()[x + y * m_colorBuffer.GetWidth()];

	HitPayload payload = TraceRay(ray);

	if (payload.HitTime < 0.0f)
	{
		glm::vec3 skyColor = glm::vec3(0.1f, 0.3f, 0.5f);
		return glm::vec4(skyColor, 1.0f);
	}

	/* Directional light
	glm::vec3 lightDir = glm::normalize(glm::vec3(-1, -1, -1));
	float lightIntensity = glm::max(glm::dot(payload.WorldNormal, -lightDir), 0.0f); // == cos(angle)
	*/

	const ISceneObject& object = m_activeScene->GetObject(payload.ObjectIndex);
	const Material& material = object.GetMaterial();

	glm::vec4 objectColor = glm::vec4(material.Color, 1.0f);
	glm::vec4 ambientColor = objectColor * 0.2f;

	return objectColor * CalcPointLight(payload) + ambientColor;
}

glm::vec4 Renderer::CalcPointLight(const HitPayload& payload) const
{
	glm::vec4 accumulatedColor(0.0f, 0.0f, 0.0f, 1.0f);

	m_activeScene->IteratePointLights(
		[&](const PointLight& light) {
			Ray ray;
			ray.Origin = payload.WorldPosition;
			ray.Direction = glm::normalize(light.Position - ray.Origin);

			/* Taking into account surface normal */
			float attenuation = glm::max(glm::dot(payload.WorldNormal, ray.Direction), 0.0f);

			HitPayload pl;
			pl.HitTime = std::numeric_limits<float>::max();
			/*
				Pixel is lit by default
				Find if pixel is overshadowed by some object
			*/
			float isLit = true;
			m_activeScene->IterateObjects(
				[&](const ISceneObject* object, int index) {
					if (isLit && object->Hit(ray, pl) && index != payload.ObjectIndex)
					{
						// Pixel is overshadowed
						isLit = false;
					}
				});

			if (isLit)
			{
				float distance = glm::length(light.Position - ray.Origin);
				attenuation *= float(light.Intensity / (0.005 * distance * distance + 1.0));
			}
			else
			{
				attenuation = 0.0f;
			}

			accumulatedColor += glm::vec4(light.LightColor * attenuation, 1.0f);
		});

	return glm::clamp(accumulatedColor, glm::vec4(0.0f), glm::vec4(1.0f));
}

HitPayload Renderer::TraceRay(const Ray& ray) const
{
	HitPayload payload;
	payload.ObjectIndex = -1;
	payload.HitTime = std::numeric_limits<float>::max();

	m_activeScene->IterateObjects(
		[&](const ISceneObject* object, int index)
		{
			if (object->Hit(ray, payload))
			{
				// New closest hit found
				payload.ObjectIndex = index;
			}
		});

	if (payload.ObjectIndex < 0)
		return Miss(ray);

	return ClosestHit(ray, payload);
}

HitPayload Renderer::ClosestHit(Ray ray, HitPayload payload) const
{
	const ISceneObject& closestObject = m_activeScene->GetObject(payload.ObjectIndex);

	ray.Transform(closestObject.GetInverseTransform());
	payload.WorldPosition = ray.At(payload.HitTime);
	payload.WorldPosition = closestObject.GetTransform() * glm::vec4(payload.WorldPosition, 1.0f);

	return payload;
}

HitPayload Renderer::Miss(const Ray&) const
{
	HitPayload payload;
	payload.HitTime = -1.0f;
	return payload;
}
