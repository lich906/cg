#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

class Shader
{
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geometryPath = nullptr);

	void Use();

	void SetUniform1i(const std::string& name, GLint value);

private:
	GLuint CompileShader(GLenum shaderType, const std::string& source);

	void CheckShaderCompileErrors(GLuint shaderId, GLenum shaderType);

	/*
		@throw std::runtime_error: If uniform with specified name wasn't found
	*/
	GLuint GetUniformLocation(const std::string& name);

	GLuint m_program;
};
