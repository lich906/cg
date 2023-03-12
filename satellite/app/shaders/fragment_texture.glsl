#version 330 core

in vec4 ourColor;
in vec2 texCoords;

out vec4 color;

uniform sampler2D u_texture;

void main()
{
	color = texture(u_texture, texCoords);
}