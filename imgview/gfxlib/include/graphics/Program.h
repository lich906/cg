#pragma once

#include "pch.h"

#include "Shader.h"

class Program
{
public:
	Program(const Program& other);
	Program(const Shader& vertex);
	Program(const Shader& vertex, const Shader& fragment);
	Program(const Shader& vertex, const Shader& fragment, const Shader& geometry);
	Program(const std::string& vertexPath);
	Program(const std::string& vertexPath, const std::string& fragmentPath);
	Program(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath);

	~Program();

	operator GLuint() const;
	const Program& operator=(const Program& other);

	void Use();

	void SetUniform1i(const std::string& name, GLint value);
	void SetUniformMatrix4fv(const std::string& name, const glm::mat4& mat);

private:
	Program();
	void Link();
	std::string GetInfoLog() const;

	GLint GetAttributeLocation(const std::string& name);
	GLint GetUniformLocation(const std::string& name);

	static inline GL::GC gc;
	GLuint m_obj;
};
