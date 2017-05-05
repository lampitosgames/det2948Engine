#pragma once
#include <vector>
#include "System.h"
#include "Handle.h"
#include "Transform.h"
#include <glm\glm.hpp>

using namespace std;
using namespace glm;

class Physics : public System {
public:
	vector<Transform> transforms;
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