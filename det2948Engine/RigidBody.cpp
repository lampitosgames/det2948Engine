#include "RigidBody.h"
#include "Transform.h"
#include "GameObject.h"
#include "Engine.h"

RigidBody::RigidBody(float mass, vec3 vel, float restitution) {
	this->mass = mass;
	this->vel = vel;
	this->accel = vec3(0.0f, 0.0f, 0.0f);
	this->restitution = restitution;
}

bool RigidBody::Start() {
	netForce = vec3(0.0f, 0.0f, 0.0f);
	return true;
}

void RigidBody::Update(float dt) {
	//Average acceleration between frames
	vec3 newAccel = vec3(0.0f, 0.0f, 0.0f);
	if (mass > 0) {
		newAccel = netForce / mass;
	}
	vec3 avgAccel = 0.5f * (accel + newAccel);
	accel = newAccel;

	//Add acceleration to the velocity scaled by dt
	vel += avgAccel * dt;
	//Add velocity to the position scaled by dt
	GetTransform()->location += vel * dt;

	//TODO: Remove temp floor collision
	//if (GetTransform()->location.y < 0 && vel.y < 0) {
	//	vel *= restitution;
	//	GetTransform()->location.y += 0.0001;
	//}

	//Reset the net force
	netForce = vec3(0.0f, 0.0f, 0.0f);
}

void RigidBody::ApplyForce(vec3 force) {
	this->netForce += force;
}
void RigidBody::ApplyGravity(vec3 grav) {
	if (this->hasGravity) {
		this->ApplyForce(this->mass * Engine::physicsSys.gravity);
	}
}
void RigidBody::ApplyDrag(float density) {
	if (this->hasDrag) {
		this->ApplyForce(-0.5f * density * cDrag * surfaceArea * vel * vel);
	}
}

Transform* RigidBody::GetTransform() {
	return this->GetGameObject()->GetComponent<Transform*>(pType::TRANSFORM);
}

float RigidBody::invMass() {
	if (mass == 0) {
		return 0.0f;
	}
	return (1.0f / mass);
}
