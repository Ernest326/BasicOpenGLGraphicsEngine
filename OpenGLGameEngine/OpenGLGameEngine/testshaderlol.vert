#version 330 core

layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aNorm;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

out vec3 normal;
out vec3 FragPos;

void main() {

	normal = mat3(transpose(inverse(model))) * aNorm; 
	FragPos = vec3(model * vec4(aPos, 1.0));

	gl_Position = projection * view * model * vec4(aPos,1.0);

}