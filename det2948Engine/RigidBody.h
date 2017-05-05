#pragma once
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"
#include <GL\glew.h>	// The order
#include <GLFW\glfw3.h> // Of these matters

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

using namespace glm;

class RigidBody : public Component {
public:
	vec3 vel;
	vec3 netForce;
	float mass;

	bool hasGravity = false;
	bool hasFriction = false;

	RigidBody(vec3 vel = vec3(0.0f, 0.0f, 0.0f), float mass = 1.0f, vec3 netForce = vec3(0.0f, 0.0f, 0.0f));

	bool Start();
	void Update();

	void ApplyForce(vec3 force);

	Transform* GetTransform();
};