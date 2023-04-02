#version 330 core

in vec2 texCoords;

out vec4 color;

uniform sampler2D u_texture;
uniform float u_additionalAlpha = 1.0;

void main()
{
	vec4 texColor = texture(u_texture, texCoords.xy);
	color = vec4(texColor.rgb, texColor.a * u_additionalAlpha);
}
