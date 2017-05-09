#include "Transform.h"

Transform::Transform() {
	location = vec3(0.0f, 0.0f, 0.0f);
	rotation = vec3(0.0f, 0.0f, 0.0f);
	scale = vec3(1.0f, 1.0f, 1.0f);
}

Transform::Transform(vec3 inLoc, vec3 inRot, vec3 inScl) {
	location = inLoc;
	rotation = inRot;
	scale = inScl;
}

vec3 Transform::Forward() {
	return rotMatrix() * vec3(0.0f, 0.0f, 1.0f);
}

vec3 Transform::Up() {
	return rotMatrix() * vec3(0.0f, 1.0f, 0.0f);
}

vec3 Transform::Left() {
	return rotMatrix() * vec3(1.0f, 0.0f, 0.0f);
}

bool Transform::Start() {
	return false;
}

void Transform::Update(float dt) {
}

mat4 Transform::modelMatrix() {
	return glm::translate(this->location) * glm::yawPitchRoll(this->rotation.y, this->rotation.x, this->rotation.z) * glm::scale(this->scale);
}

mat3 Transform::rotMatrix() {
	return (mat3)yawPitchRoll(rotation.y, rotation.x, rotation.z);
}
