#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 3) in vec2 a_texCoords;

out vec4 VertexColor;

uniform mat4 m_model;
uniform mat4 m_view;
uniform mat4 m_projection;

void main()
{
	gl_Position = m_projection * m_view * m_model * vec4(a_position, 1.0);
	VertexColor = vec4(1.0, 1.0, 1.0, 1.0);
}
