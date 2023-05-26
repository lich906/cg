#pragma once

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

	HitPayload TraceRay(const Ray& ray) const;
	HitPayload ClosestHit(Ray ray, HitPayload payload) const;
	HitPayload Miss(const Ray& ray) const;

	const Scene* m_activeScene;
	const Camera* m_activeCamera;

	ColorBuffer m_colorBuffer;
	std::vector<uint32_t> m_horizontalIndices, m_verticalIndices;
};
