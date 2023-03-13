#include "opengl_abstractions/Shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geometryPath)
{
	std::string vertexCode, fragmentCode, geometryCode;
	std::ifstream vShaderFile, fShaderFile, gShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		if (!vShaderFile.is_open() || !fShaderFile.is_open())
		{
			throw std::runtime_error("ERROR::SHADER::FAILED_TO_OPEN_FILE");
		}

		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

		if (geometryPath != nullptr)
		{
			gShaderFile.open(geometryPath);
			std::stringstream gShaderStream;
			gShaderStream << gShaderFile.rdbuf();
			gShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (std::ifstream::failure e)
	{
		throw std::runtime_error("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
	}

	// 2. Compile shaders
	GLuint
		vertex = CompileShader(GL_VERTEX_SHADER, vertexCode),
		fragment = CompileShader(GL_FRAGMENT_SHADER, fragmentCode);
	// If geometry shader is given, compile geometry shader
	GLuint geometry;
	if (geometryPath != nullptr)
	{
		geometry = CompileShader(GL_GEOMETRY_SHADER, geometryCode);
	}
	// Shader Program
	m_program = glCreateProgram();
	glAttachShader(m_program, vertex);
	glAttachShader(m_program, fragment);
	if (geometryPath != nullptr)
		glAttachShader(m_program, geometry);
	glLinkProgram(m_program);
	GLint success;
	GLchar infoLog[1024];
	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_program, 1024, NULL, infoLog);
		throw std::runtime_error(
			"| ERROR::PROGRAM-LINKING-ERROR |\n" + std::string(infoLog) + 
			"\n| -- --------------------------------------------------- -- |");
	}
	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	if (geometryPath != nullptr)
		glDeleteShader(geometry);
}

void Shader::Use()
{
	glUseProgram(m_program);
}

void Shader::SetUniform1i(const std::string& name, GLint value)
{
	auto location = GetUniformLocation(name);
	glUseProgram(m_program);
	glUniform1i(location, value);
}

GLuint Shader::CompileShader(GLenum shaderType, const std::string& source)
{
	GLuint shaderId = glCreateShader(shaderType);
	const GLchar* sourceData = source.c_str();
	glShaderSource(shaderId, 1, &sourceData, nullptr);
	glCompileShader(shaderId);

	CheckShaderCompileErrors(shaderId, shaderType);

	return shaderId;
}

void Shader::CheckShaderCompileErrors(GLuint shaderId, GLenum shaderType)
{
	GLint success;

	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		throw std::runtime_error("ERROR::SHADER-COMPILATION-ERROR Shader type: " + std::to_string(shaderType));
	}
}

GLuint Shader::GetUniformLocation(const std::string& name)
{
	GLuint location = glGetUniformLocation(m_program, name.c_str());
	if (location >= 0)
	{
		return location;
	}

	throw std::runtime_error("Uniform with name '" + name + "' not found in shader program.");
}
