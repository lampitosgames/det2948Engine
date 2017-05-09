#pragma once
#include <vector>
#include "System.h"
#include "Handle.h"
#include "Transform.h"
#include "RigidBody.h"
#include <glm\glm.hpp>

using namespace std;
using namespace glm;

class Physics : public System {
public:
	vector<Transform> transforms;
	int transCount = 0;
	vector<RigidBody> rigidBodies;
	int rbCount = 0;

	//Physics constants
	vec3 gravity = vec3(0.0f, -9.81f, 0.0f);
	float airDensity = 1.2f;

	bool Start();
	void Update(float dt);

	template<typename T> T Get(Handle h);
	Handle Add(int indexPointer, pType type);

	/*

	COMPONENTS

	*/
	Handle CreateTransform(vec3 inLoc, vec3 inRot, vec3 inScl);
	Handle CreateRigidBody(float mass = 1.0f, vec3 vel = vec3(0.0f, 0.0f, 0.0f));
};