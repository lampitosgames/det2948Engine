#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

out vec3 fragPos;
out vec3 outNormal;
out vec2 blendedUV;

uniform mat4 camMatrix;
uniform mat4 modelMatrix;

void main() {
	gl_Position = camMatrix * modelMatrix * vec4(position, 1.0f);
	fragPos = vec3(modelMatrix * vec4(position, 1.0f));
	outNormal = mat3(transpose(inverse(modelMatrix))) * normal;
	blendedUV = uv;
}