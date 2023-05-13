#version 330 core

in vec2 TexCoords;
in vec3 VertexNormal;
in vec3 FragPos;

out vec4 color;

uniform vec3 u_viewPos;
uniform vec3 u_lightPosition;
uniform vec4 u_lightColor;
uniform float u_ambientValue;
uniform sampler2D u_texture;

float specularValue = 0.5f;

void main()
{
	// Ambient
	vec4 ambientColor = u_ambientValue * u_lightColor;

	// Diffuse
	vec3 lightDir = normalize(u_lightPosition - FragPos);
	vec3 norm = normalize(VertexNormal);

	float diffusion = max(dot(norm, lightDir), 0.0);
	vec4 diffuseColor = diffusion * u_lightColor;

	//Specular
	vec3 viewDir = normalize(u_viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
	vec4 specularColor = specularValue * spec * u_lightColor;

	color = (ambientColor + diffuseColor + specularColor) * texture(u_texture, TexCoords);
}
