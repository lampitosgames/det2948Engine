#pragma once
#include "System.h"
#include <GL\glew.h>	// The order
#include <GLFW\glfw3.h> // Of these matters
#include <glm\glm.hpp>

static class Input {
public:
	static bool Start();
	static void Update(float dt);

	static bool Key(unsigned glfwKey);
	static bool KeyDown(unsigned glfwKey);
	static bool KeyUp(unsigned glfwKey);

	static glm::vec2 MouseDelta();
	static glm::vec2 MousePos();
};