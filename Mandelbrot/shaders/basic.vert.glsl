#version 400 core
layout (location = 0) in vec2 vertexPosition;

out vec2 fragPos;

uniform mat4 pr_matrix;

void main() {
	fragPos = vertexPosition;
	gl_Position = pr_matrix * vec4(vertexPosition, 1.0f, 1.0f);
}
