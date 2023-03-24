#include "graphics/Shader.h"

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
	GlCall(m_program = glCreateProgram());
	GlCall(glAttachShader(m_program, vertex));
	GlCall(glAttachShader(m_program, fragment));
	if (geometryPath != nullptr)
	{
		GlCall(glAttachShader(m_program, geometry));
	}
	GlCall(glLinkProgram(m_program));
	GLint success;
	GLchar infoLog[1024];
	GlCall(glGetProgramiv(m_program, GL_LINK_STATUS, &success));
	if (!success)
	{
		GlCall(glGetProgramInfoLog(m_program, 1024, NULL, infoLog));
		throw std::runtime_error(
			"| ERROR::PROGRAM-LINKING-ERROR |\n" + std::string(infoLog) + 
			"\n| -- --------------------------------------------------- -- |");
	}
	// Delete the shaders as they're linked into our program now and no longer necessery
	GlCall(glDeleteShader(vertex));
	GlCall(glDeleteShader(fragment));
	if (geometryPath != nullptr)
	{
		GlCall(glDeleteShader(geometry));
	}
}

void Shader::Use()
{
	GlCall(glUseProgram(m_program));
}

void Shader::SetUniform1i(const std::string& name, GLint value)
{
	auto location = GetUniformLocation(name);
	GlCall(glUseProgram(m_program));
	GlCall(glUniform1i(location, value));
}

void Shader::SetUniformMatrix4fv(const std::string& name, const glm::mat4& mat)
{
	auto location = GetUniformLocation(name);
	GlCall(glUseProgram(m_program));
	GlCall(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat)));
}

GLuint Shader::CompileShader(GLenum shaderType, const std::string& source)
{
	GlCall(GLuint shaderId = glCreateShader(shaderType));
	const GLchar* sourceData = source.c_str();
	GlCall(glShaderSource(shaderId, 1, &sourceData, nullptr));
	GlCall(glCompileShader(shaderId));

	CheckShaderCompileErrors(shaderId, shaderType);

	return shaderId;
}

void Shader::CheckShaderCompileErrors(GLuint shaderId, GLenum shaderType) const
{
	GLint success;

	GlCall(glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success));
	if (!success)
	{
		throw std::runtime_error("ERROR::SHADER-COMPILATION-ERROR Shader type: " + std::to_string(shaderType));
	}
}

GLuint Shader::GetUniformLocation(const std::string& name)
{
	GlCall(GLuint location = glGetUniformLocation(m_program, name.c_str()));

	if (location >= 0)
	{
		return location;
	}

	throw std::runtime_error("Uniform with name '" + name + "' not found in shader program.");
}
