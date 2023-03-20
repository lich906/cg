#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 textureCoords;

out vec4 ourColor;
out vec2 texCoords;

uniform mat4 m_model;
uniform mat4 m_view;
uniform mat4 m_projection;

void main()
{
	gl_Position = m_projection * m_view * m_model * vec4(position, 0.0, 1.0);
	ourColor = color;
	texCoords = textureCoords;
}
