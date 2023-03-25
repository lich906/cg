#pragma once

#include "types/Vector.h"

namespace config
{

constexpr float GravitationCoeff = 1.0f;
const Vector MoonInitialPosition = { 100.0f, 200.0f };
const Vector EarthInitialPosition = { 400.0f, 500.0f };
constexpr float MoonScale = 20.0f;
constexpr float EarthScale = 50.0f;
constexpr float MoonMass = 20.0f;
constexpr float EarthMass = 40000.0f;
constexpr float Timestep = 0.05f;

namespace graphics
{

constexpr int WindowWidth = 1280;
constexpr int WindowHeight = 720;
constexpr int GlfwContextVersionMajor = 3;
constexpr int GlfwContextVersionMinor = 3;
constexpr auto GlslVersion = "#version 330";
constexpr int GlfwSamples = 4;

} // namespace graphics

} // namespace config