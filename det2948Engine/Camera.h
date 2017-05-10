#pragma once
#include "GameObject.h"
#include <GL\glew.h>	// The order
#include <GLFW\glfw3.h> // Of these matters
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

using namespace glm;

class Camera : public GameObject {
public:
	//Perspective
	float fov = .4 * 3.14;
	float aspectRatio = 1.7777777777f;
	float near = 0.01f;
	float far = 1000.0f;

	//Rotation matrices
	mat4 lookAtMatrix;
	mat4 projMatrix;
	mat4 camMatrix;

	Camera();
	void Start();
	void Update();
	void HandleInput();
};