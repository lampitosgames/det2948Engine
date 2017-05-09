#include "Physics.h"
#include "Engine.h"

bool Physics::Start() {
	for (int i = 0; i < transCount; i++) {
		transforms[i].Start();
	}
	for (int i = 0; i < rbCount; i++) {
		rigidBodies[i].Start();
	}
	return true;
}

void Physics::Update(float dt) {
	for (int i = 0; i < transCount; i++) {
		transforms[i].Update(dt);
	}
	for (int i = 0; i < rbCount; i++) {
		rigidBodies[i].ApplyGravity(gravity);
		rigidBodies[i].ApplyDrag(airDensity);
		rigidBodies[i].Update(dt);
	}
}

Handle Physics::Add(int indexPointer, pType type) {
	return Engine::OF.Add(indexPointer, type);
}

template<typename T>
inline T Physics::Get(Handle h) {
	return Engine::OF.Get<T>(h);
}

/*

COMPONENTS

*/
Handle Physics::CreateTransform(vec3 inLoc, vec3 inRot, vec3 inScl) {
	transforms.push_back(Transform(inLoc, inRot, inScl));
	transCount += 1;
	Handle transformHandle = Add(transCount - 1, pType::TRANSFORM);
	transforms[transCount - 1].handle = transformHandle;
	transforms[transCount - 1].index = transCount - 1;
	return transformHandle;
}

Handle Physics::CreateRigidBody(float mass, vec3 vel) {
	rigidBodies.push_back(RigidBody(mass, vel));
	rbCount += 1;
	Handle rigidBodyHandle = Add(rbCount - 1, pType::RIGID_BODY);
	rigidBodies[rbCount - 1].handle = rigidBodyHandle;
	rigidBodies[rbCount - 1].index = rbCount - 1;
	return rigidBodyHandle;
}
