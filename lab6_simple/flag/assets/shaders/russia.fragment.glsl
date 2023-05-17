#version 330 core

in vec3 FragPos;

out vec4 color;

vec4 GetFlagColor(float h);

void main()
{
	color = GetFlagColor(FragPos.y);
}

vec4 GetFlagColor(float h)
{
	if (h > 0.2222)
	{
		return vec4(1.0);
	}
	else if (h > -0.2222)
	{
		return vec4(0.0, 0.0, 1.0, 1.0);
	}
	else
	{
		return vec4(1.0, 0.0, 0.0, 1.0);
	}
}
