#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

out vec3 vertColor;

uniform mat4 camMatrix;

void main() {
	vertColor = position;
	gl_Position = camMatrix * vec4(position, 1);
}