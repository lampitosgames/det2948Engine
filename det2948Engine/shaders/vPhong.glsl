#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

out vec3 outNormal;
out vec3 outPos;
out vec2 blendedUV;

uniform mat4 camMatrix;
uniform mat4 modelMatrix;

void main() {
	gl_Position = camMatrix * modelMatrix * vec4(position, 1);
	outNormal = normal;
	outPos = position;
	blendedUV = uv;
}