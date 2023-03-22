#pragma once

#include <optional>

#include "Shader.h"

class CurrentShader
{
public:
	/*
		Pass ownership of shader, since we will have global access to it.
	*/
	static void Set(Shader&& shader);

	static Shader& Get();

private:
	CurrentShader() = delete;

	inline static std::optional<Shader> m_shader;
};
