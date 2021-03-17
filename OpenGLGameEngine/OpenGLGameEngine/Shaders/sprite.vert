#version 330 core

layout (location = 0) in vec4 vertex;

uniform mat4 projection;
uniform mat4 model;

out vec2 TexCoord;

void main() {

	TexCoord = vertex.zw;
	gl_Position = model * vec4(vertex.xy, 0.0, 1.0);

}