#include "Engine.h"
#include "Timer.h"
#include "Handle.h"
#include <map>
#include <FreeImage.h>

#include <GL\glew.h>	// The order
#include <GLFW\glfw3.h> // Of these matters

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

namespace {
	map<int, bool> keyIsDown;
	map<int, bool> keyWasDown;

	void mouseClick(GLFWwindow* windowPtr, int button, int action, int mods) {
		keyIsDown[button] = action;
	}

	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		keyIsDown[key] = action;
		switch (key) {
		case GLFW_KEY_ESCAPE:
			if (action == GLFW_RELEASE) {
				glfwSetWindowShouldClose(Engine::windowSys.window, GL_TRUE);
			}
			break;
		default:
			break;
		}
	}
}


Timer Engine::time = Timer();
Render Engine::renderSys = Render();
Window Engine::windowSys = Window();
ObjectFactory Engine::OF = ObjectFactory();

bool Engine::Start() {
	if (!Engine::windowSys.Start()) {
		cout << "\nWindow system failed to start";
		return false;
	}

	//Link inputs to openGL
	glfwSetMouseButtonCallback(Engine::windowSys.window, mouseClick);
	glfwSetKeyCallback(Engine::windowSys.window, keyCallback);
	//Hide the cursor
	glfwSetInputMode(Engine::windowSys.window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	if (!Engine::renderSys.Start()) {
		cout << "\nRender system failled to start";
		return false;
	}

	if (!Engine::OF.Start()) {
		cout << "\Object Factory failled to start";
		return false;
	}

	return true;
}

void Engine::Update(float dt) {
	//Update inputs
	keyWasDown = keyIsDown;
	glfwPollEvents();
	//Update systems
	Engine::windowSys.Update(dt);
	Engine::renderSys.Update(dt);
	Engine::OF.Update(dt);

	//TEMP : Handle inputs
	Engine::HandleCameraInput();


}

void Engine::GameLoop() {
	while (!glfwWindowShouldClose(Engine::windowSys.window)) {
		time.Update();
		Engine::Update(time.dt);
		//Copy back buffer to front.  Everything was rendered on the back buffer so now we display it
		glfwSwapBuffers(Engine::windowSys.window);
	}
}

void Engine::HandleCameraInput() {
	Camera* curCamera = Engine::OF.Get<Camera*>(Engine::renderSys.curCamera);
	//Camera location vector
	glm::vec3* cl = &((*curCamera).loc);
	//Camera rotation vector
	glm::vec3* cr = &((*curCamera).rot);

	glm::mat3 R = (glm::mat3)glm::yawPitchRoll((*cr).y, (*cr).x, (*cr).z);

	//Rotation sensitivity
	float hSens = 0.003; //Side to side
	float vSens = 0.003;  //Up and down

						  //Mouse Input
	int w = Engine::windowSys.screenWidth, h = Engine::windowSys.screenHeight;
	double x, y;
	glfwGetCursorPos(Engine::windowSys.window, &x, &y);
	//Reference to the rotation matrix
	(*cr).y -= hSens * (x - w * 0.5f); //yaw
	(*cr).x -= vSens * (y - h * 0.5f); //pitch
	(*cr).x = glm::clamp((*cr).x, -0.5f*3.1415f, 0.5f*3.1415f);

	//Set cursor to center of window
	glfwSetCursorPos(Engine::windowSys.window, w*0.5f, h*0.5f);

	//Keyboard input
	glm::vec3 vel = (*curCamera).vel;

	if (glfwGetKey(Engine::windowSys.window, GLFW_KEY_D)) {
		vel += R * glm::vec3(1, 0, 0);
	}
	if (glfwGetKey(Engine::windowSys.window, GLFW_KEY_A)) {
		vel += R * glm::vec3(-1, 0, 0);
	}
	if (glfwGetKey(Engine::windowSys.window, GLFW_KEY_W)) {
		vel += R * glm::vec3(0, 0, -1);
	}
	if (glfwGetKey(Engine::windowSys.window, GLFW_KEY_S)) {
		vel += R * glm::vec3(0, 0, 1);
	}
	if (glfwGetKey(Engine::windowSys.window, GLFW_KEY_R)) {
		vel += R * glm::vec3(0, 1, 0);
	}
	if (glfwGetKey(Engine::windowSys.window, GLFW_KEY_F)) {
		vel += R * glm::vec3(0, -1, 0);
	}

	float speed = 4.0f;
	if (vel != glm::vec3()) {
		(*curCamera).vel = glm::normalize(vel) * speed * Engine::time.dt;
	}
}

