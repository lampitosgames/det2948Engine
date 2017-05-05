class GameObject;
#include "RigidBody.h"

RigidBody::RigidBody(vec3 vel, float mass, vec3 netForce) {
	this->vel = vel;
	this->mass = mass;
	this->netForce = netForce;
}

bool RigidBody::Start() {
	return true;
}

void RigidBody::Update() {
	vec3 accel = this->netForce / this->mass;
	this->vel += accel;
	GetTransform()->location += this->vel;
}

void RigidBody::ApplyForce(vec3 force) {
	this->netForce += force;
}

Transform* RigidBody::GetTransform() {
	return this->GetGameObject()->GetComponent<Transform*>(pType::TRANSFORM);
}
