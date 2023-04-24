#version 330 core

in vec4 VertexColor;
in vec3 VertexNormal;
in vec3 FragPos;

out vec4 color;

uniform vec3 u_lightPosition;
uniform vec4 u_lightColor;

void main()
{
	float ambientValue = 0.1f;
	vec4 ambientColor = ambientValue * u_lightColor;

	vec3 lightDir = normalize(u_lightPosition - FragPos);
	vec3 norm = normalize(VertexNormal);

	float diffusion = max(dot(norm, lightDir), 0.0);
	vec4 diffuseColor = diffusion * u_lightColor;

	color = (ambientColor + diffuseColor) * VertexColor;
}
