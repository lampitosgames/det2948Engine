#include "Input.h"
#include "Engine.h"
#include <map>

namespace {
	map<int, bool> keyState;
	map<int, bool> prevKeyState;

	double cursorPos[2];
	double prevCursorPos[2];

	void mouseCallback(GLFWwindow* windowPtr, int button, int action, int mods) {
		keyState[button] = action;
	}

	void mousePosCallback(GLFWwindow* window, double xpos, double ypos) {
		cursorPos[0] = xpos;
		cursorPos[1] = ypos;
	}

	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		keyState[key] = action;
	}
}

bool Input::Start() {
	//Link inputs to openGL
	glfwSetMouseButtonCallback(Engine::windowSys.window, mouseCallback);
	glfwSetCursorPosCallback(Engine::windowSys.window, mousePosCallback);
	glfwSetKeyCallback(Engine::windowSys.window, keyCallback);

	//Get the initial cursor position
	glfwGetCursorPos(Engine::windowSys.window, &cursorPos[0], &cursorPos[1]);
	prevCursorPos[0] = cursorPos[0];
	prevCursorPos[1] = cursorPos[1];
	//Hide the cursor
	glfwSetInputMode(Engine::windowSys.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	return true;
}

void Input::Update(float dt) {
	//Update inputs
	prevKeyState = keyState;
	prevCursorPos[0] = cursorPos[0];
	prevCursorPos[1] = cursorPos[1];
	glfwPollEvents();
}

bool Input::Key(unsigned glfwKey) {
	return keyState[glfwKey] == GLFW_PRESS;
}

bool Input::KeyDown(unsigned glfwKey) {
	return (keyState[glfwKey] == GLFW_PRESS && prevKeyState[glfwKey] == GLFW_RELEASE);
}

bool Input::KeyUp(unsigned glfwKey) {
	return (keyState[glfwKey] == GLFW_RELEASE && prevKeyState[glfwKey] == GLFW_PRESS);
}

glm::vec2 Input::MouseDelta() {
	return glm::vec2(cursorPos[0] - prevCursorPos[0], cursorPos[1] - prevCursorPos[1]);
}

glm::vec2 Input::MousePos() {
	return glm::vec2(cursorPos[0], cursorPos[1]);
}
