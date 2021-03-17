#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D sprite;
uniform vec3 spriteColor;

void main() {
	
	vec4 texColor = vec4(spriteColor, 1.0) * texture(sprite, vec2(TexCoord.x, -TexCoord.y));

	if(texColor.a < 0.1) {
		discard;
	}

	FragColor = texColor;

}