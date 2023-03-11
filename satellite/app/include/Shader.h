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

private:
	GLuint CompileShader(GLenum shaderType, const std::string& source);

	void CheckShaderCompileErrors(GLuint shaderId, GLenum shaderType);

	GLuint m_program;
};
