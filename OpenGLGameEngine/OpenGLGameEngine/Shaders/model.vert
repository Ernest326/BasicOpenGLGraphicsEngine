#version 330 core

layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 _Normal;
layout (location = 2) in vec2 _TexCoords;

out vec4 FragPos;

out vec2 TexCoords;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {

	TexCoords = _TexCoords;
	Normal = _Normal;

	FragPos = projection * view * model * vec4(Pos, 1);

}