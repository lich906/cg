#version 330 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texCoords;

out vec2 TexCoords;

uniform mat4 u_VPMatrix;

void main()
{
	TexCoords = a_texCoords;
	gl_Position = u_VPMatrix * vec4(a_position, 1.0);
}
