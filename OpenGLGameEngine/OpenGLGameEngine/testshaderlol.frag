#version 330 core

in vec3 normal;
in mat4 _model;
in vec3 FragPos;

uniform vec3 viewPos;
uniform vec3 lightPosition;

out vec3 FragColor;

void main() {

	vec3 Color = vec3(1.0, 0.0, 0.0);

	float ambientamount = 0.1;
	vec3 ambient = Color * ambientamount;

	vec3 result = Color;

	FragColor = result;

}