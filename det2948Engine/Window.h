#pragma once
#include "System.h"

#include <GL\glew.h>	// The order
#include <GLFW\glfw3.h> // Of these matters

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

class Window : public System {
public:
	GLFWwindow* window;
	int screenWidth, screenHeight;

	Window();

	bool Start();
	void Update(float dt);

	~Window();
};