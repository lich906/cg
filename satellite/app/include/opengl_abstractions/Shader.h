#pragma once

#include "glad_glfw.h"

#include "glm/matrix.hpp" // mat4
#include "glm/gtc/type_ptr.hpp" // value_ptr

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

class Shader
{
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geometryPath = nullptr);

	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;

	Shader(Shader&&) = default;
	Shader& operator=(Shader&&) = default;

	void Use();

	void SetUniform1i(const std::string& name, GLint value);

	void SetUniformMatrix4fv(const std::string& name, const glm::mat4& mat);

private:
	GLuint CompileShader(GLenum shaderType, const std::string& source);

	void CheckShaderCompileErrors(GLuint shaderId, GLenum shaderType);

	/*
		@throw std::runtime_error: If uniform with specified name wasn't found
	*/
	GLuint GetUniformLocation(const std::string& name);

	GLuint m_program;
};
