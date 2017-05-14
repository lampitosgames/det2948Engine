#include "Collider.h"
#include "pType.h"
#include "GameObject.h"

bool Collider::Start() {
	return true;
}

void Collider::Update(float dt) {
}

Transform* Collider::GetTransform() {
	return this->GetGameObject()->GetComponent<Transform*>(pType::TRANSFORM);
}

RigidBody* Collider::GetRigidBody() {
	return this->GetGameObject()->GetComponent<RigidBody*>(pType::RIGID_BODY);
}

vec3 Collider::pos() {
	return GetTransform()->location;
}
vec3 Collider::vel() {
	return GetRigidBody()->vel;
}
vec3 Collider::scale() {
	return GetTransform()->scale;
}
