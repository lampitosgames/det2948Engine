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

class BouncingBall : public GameObject {
public:
	void Start() {
	};
	void Update() {
		if (Input::KeyDown(GLFW_MOUSE_BUTTON_1)) {
			GetComponent<RigidBody*>(pType::RIGID_BODY)->ApplyForce(vec3(0.0f, 1000.0f, 0.0f));
		}
		if (Input::KeyDown(GLFW_KEY_N)) {
			GetComponent<Transform*>(pType::TRANSFORM)->location = vec3(0.0f, 30.0f, 0.0f);
			GetComponent<RigidBody*>(pType::RIGID_BODY)->accel = vec3();
			GetComponent<RigidBody*>(pType::RIGID_BODY)->vel = vec3();
		}
	};
};