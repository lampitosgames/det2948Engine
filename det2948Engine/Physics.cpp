#include "Physics.h"
#include "Engine.h"

bool Physics::Start() {
	return true;
}

void Physics::Update(float dt) {
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
	transforms[transCount++] = Transform(inLoc, inRot, inScl);
	Handle transformhandle = Add(transCount - 1, pType::TRANSFORM);
	transforms[transCount - 1].handle = transformhandle;
	transforms[transCount - 1].index = transCount - 1;
	return transformhandle;
}