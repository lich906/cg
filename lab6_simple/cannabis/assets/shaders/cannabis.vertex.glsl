#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec4 a_color;

uniform mat4 m_model;
uniform mat4 m_view;
uniform mat4 m_projection;

void main()
{
	float x = a_position.x;
	float r = (1.0 + sin(x)) * ( 1 + 0.9 * cos(8 * x)) * (1 + 0.1 * cos(24 * x)) * (0.5 + 0.05 * cos(140 * x));

	gl_Position = m_projection * m_view * m_model * vec4(r * cos(x), r * sin(x), 1.0, 1.0);
}
