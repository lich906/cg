#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec4 a_color;

out vec4 VertexColor;
out vec3 VertexNormal;
out vec3 FragPos;

uniform mat4 m_model;
uniform mat4 m_view;
uniform mat4 m_projection;
uniform vec3 u_normalMultiplier;
uniform float u_t;
uniform float u_b_coeff;
uniform float u_a_coeff;

void main()
{
	vec4 p = vec4(a_position, 1.0);
	p.y = (2 * u_t - 1) * pow(p.z, 2) / pow(u_b_coeff, 2) + pow(p.x, 2) / pow(u_a_coeff, 2);
	vec4 worldPos = m_model * p;
	gl_Position = m_projection * m_view * m_model * p;
	VertexColor = a_color;
	VertexNormal = -vec3(u_normalMultiplier.x * a_position.x, -1.0f, u_normalMultiplier.z * a_position.z);
	FragPos = vec3(worldPos);
}
