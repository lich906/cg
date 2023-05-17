#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec4 a_color;

out vec3 FragPos;

uniform mat4 m_model;
uniform mat4 m_view;
uniform mat4 m_projection;

void main()
{
	gl_Position = m_projection * m_view * m_model * vec4(a_position, 1.0);
	FragPos = vec3(m_model * vec4(a_position, 1.0));
}
