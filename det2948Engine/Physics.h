#pragma once
#include <vector>
#include "Transform.h"
#include "System.h"
#include <glm\glm.hpp>

using namespace std;

class Physics : public System {
public:
	Transform transforms[typeArraySize];
	int transCount = 0;

	bool Start();
	void Update(float dt);

	template<typename T> T Get(Handle h);

	Handle Add(int indexPointer, pType type);


	/*

	COMPONENTS

	*/
	Handle CreateTransform(vec3 inLoc, vec3 inRot, vec3 inScl);
};