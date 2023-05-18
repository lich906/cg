#version 330 core

in vec4 VertexColor;
in vec3 VertexNormal;
in vec3 FragPos;

out vec4 color;

uniform vec3 u_viewPos;
uniform vec3 u_lightPosition;
uniform vec4 u_lightColor;
uniform float u_ambientValue;

float specularValue = 0.5f;

vec4 GetVertexColor(float height)
{
	float gradientWidth = 1.0;
	if (height > gradientWidth * 2)
	{
		return vec4(1.0, 0.0, 0.0, 1.0);
	}
	if (height > gradientWidth)
	{
		return vec4(1.0, (height - gradientWidth * 2) / -gradientWidth, 0.0, 1.0);
	}
	if (height > 0.0)
	{
		return vec4(height / gradientWidth, 1.0, 0.0, 1.0);
	}
	if (height > -gradientWidth)
	{
		return vec4(0.0, 1.0, height / -gradientWidth, 1.0);
	}
	if (height > -gradientWidth * 2)
	{
		return vec4(0.0, (gradientWidth * 2 + height) / gradientWidth, 1.0, 1.0);
	}
	return vec4(0.0, 0.0, 1.0, 1.0);
}

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

	color = (ambientColor + diffuseColor + specularColor) * GetVertexColor(FragPos.y);
}
