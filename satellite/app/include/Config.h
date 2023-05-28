#pragma once

#include <glm/glm.hpp>

namespace config
{

constexpr float GravitationCoeff = 1.0f;
constexpr glm::vec2 MoonInitialPosition = { 100.0f, 200.0f };
constexpr glm::vec2 EarthInitialPosition = { 400.0f, 500.0f };
constexpr glm::vec2 MarsInitialPosition = { 500.0f, 200.0f };
constexpr float MoonScale = 20.0f;
constexpr float EarthScale = 50.0f;
constexpr float MarsScale = 30.0f;
constexpr float MoonMass = 20.0f;
constexpr float MarsMass = 2000.0f;
constexpr float EarthMass = 80000.0f;
constexpr float Timestep = 0.05f;
constexpr float ArrowScaleCoeff = 2.0f;
constexpr float ExplosionInitialScale = 50.0f;
constexpr float ExplosionAnimationTime = 20.0f;

namespace graphics
{

constexpr int WindowWidth = 1280;
constexpr int WindowHeight = 720;
constexpr int GlfwContextVersionMajor = 3;
constexpr int GlfwContextVersionMinor = 3;
constexpr auto GlslVersion = "#version 330";
constexpr int GlfwSamples = 4;
constexpr struct {
	float r = 0.0f, g = 0.05f, b = 0.1f, a = 1.0f;
} ClearColor;

} // namespace graphics

} // namespace config
