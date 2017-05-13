#include "SphereCollider.h"

SphereCollider::SphereCollider(float radius) {
	this->type = colType::SPHERE_COL;
	this->radius = radius;
}

bool SphereCollider::Start() {
	return true;
}

void SphereCollider::Update(float dt) {
}

float SphereCollider::maxScale() {
	vec3 curScale = scale();
	return max(curScale.x, max(curScale.y, curScale.z));
}
