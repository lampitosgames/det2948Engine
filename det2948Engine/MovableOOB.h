#pragma once
#include "GameObject.h"
#include "Input.h"
#include "Transform.h"
#include "RigidBody.h"
#include "pType.h"
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

using namespace glm;

class MovableOOB : public GameObject {
public:
	vec3 startLoc = vec3();
	void Start() {
	};
	void Update() {
		if (startLoc == vec3()) {
			this->startLoc = GetComponent<Transform*>(pType::TRANSFORM)->location;
		}
		if (Input::KeyDown(GLFW_KEY_N)) {
			GetComponent<Transform*>(pType::TRANSFORM)->location = this->startLoc;
			GetComponent<RigidBody*>(pType::RIGID_BODY)->accel = vec3();
			GetComponent<RigidBody*>(pType::RIGID_BODY)->vel = vec3();
		}

		//Move down
		if (Input::Key(GLFW_KEY_K)) {
			GetComponent<RigidBody*>(pType::RIGID_BODY)->ApplyForce(vec3(0.0f, -1.0f, 0.0f));
		}
		//Move left
		if (Input::Key(GLFW_KEY_J)) {
			GetComponent<RigidBody*>(pType::RIGID_BODY)->ApplyForce(vec3(-1.0f, 0.0f, 0.0f));
		}
		//Move right
		if (Input::Key(GLFW_KEY_L)) {
			GetComponent<RigidBody*>(pType::RIGID_BODY)->ApplyForce(vec3(1.0f, 0.0f, 0.0f));
		}
		//Move up
		if (Input::Key(GLFW_KEY_I)) {
			GetComponent<RigidBody*>(pType::RIGID_BODY)->ApplyForce(vec3(0.0f, 1.0f, 0.0f));
		}
	};
};