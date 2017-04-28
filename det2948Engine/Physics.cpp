#include "Physics.h"
#include "Engine.h"

bool Physics::Start() {
	return true;
}

void Physics::Update(float dt) {
}

void* Physics::Get(Handle h) {
	return Engine::OF.Get(h);
}

Handle Physics::Add(void* pointer, pType type) {
	return Engine::OF.Add(pointer, type);
}

/*

COMPONENTS

*/
Handle Physics::CreateTransform(vec3 inLoc, vec3 inRot, vec3 inScl) {
	transforms.push_back(Transform(inLoc, inRot, inScl));
	Handle transformhandle = Add(&transforms[transforms.size() - 1], pType::TRANSFORM);
	transforms[transforms.size() - 1].handle = transformhandle;
	return transformhandle;
}