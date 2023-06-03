#pragma once

#include <optional>

#include "Scene.h"
#include "Camera.h"
#include "ColorBuffer.h"

class Renderer
{
public:
	void OnResize(size_t width, size_t height);
	void Render(const Scene& scene, const Camera& camera);
	const ColorBuffer& GetColorBuffer() const;

private:
	glm::vec4 GetPixelColor(uint32_t x, uint32_t y) const;
	glm::vec4 CalcPointLight(const HitPayload& payload) const;
	glm::vec4 CalcDirectLight(const HitPayload& payload) const;
	glm::vec4 CalcAmbientLight(const HitPayload& payload) const;

	HitPayload TraceRay(const Ray& ray) const;
	HitPayload ClosestHit(const Ray& ray, HitPayload payload) const;
	HitPayload Miss(const Ray& ray) const;

	/*
		Find if ray is collided with any object of the scene
	*/
	std::optional<float> GetLowestHitTime(const Ray& ray) const;

	const Scene* m_activeScene;
	const Camera* m_activeCamera;

	ColorBuffer m_colorBuffer;
	std::vector<uint32_t> m_horizontalIndices, m_verticalIndices;
};
