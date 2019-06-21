#version 400 core

in vec2 fragPos;
out vec4 color;

uniform sampler2D unif_texture;

void main() {
	color = texture(unif_texture, fragPos);
}