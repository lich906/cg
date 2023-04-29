#pragma once

#include "glad/glad.h"
#include "glm/glm.hpp"

namespace consts
{

constexpr glm::vec4 BACKGROUND_COLOR = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
constexpr glm::vec4 LIGHT_COLOR = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
constexpr glm::vec4 SURFACE_COLOR = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
constexpr glm::vec3 SURFACE_POSITION = glm::vec3(0.0f, 0.0f, -4.0f);
constexpr glm::vec3 LIGHT_SOURCE_INIT_POS = glm::vec3(0.0f, 0.0f, 0.0f);
constexpr float AMBIENT_LIGHT_VALUE = 0.05f;
constexpr float SURFACE_SIZE = 30.0f;
constexpr float SURFACE_QUAD_SIZE = 0.05f;
constexpr GLuint PRIMITIVE_RESTART_INDEX = (GLuint)-1;

} // namespace consts
