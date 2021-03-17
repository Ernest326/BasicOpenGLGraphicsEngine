#version 330 core

out vec4 FragColor;
in vec2 TexCoord;

uniform vec3 objectColor;

uniform sampler2D texture1;

void main()
{
	float gamma = 1.2;
	vec3 diffuseColor = pow(texture(texture1, TexCoord).rgb, vec3(gamma));

    FragColor = vec4(diffuseColor, 1.0);
} 