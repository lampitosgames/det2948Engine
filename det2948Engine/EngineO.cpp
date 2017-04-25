#include "EngineO.h"
#include "Shader.h"
#include "Mesh.h"
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
					glfwSetWindowShouldClose(EngineO::windowPtr, GL_TRUE);
				}
				break;
			default:
				break;
		}
	}
}

GLFWwindow* EngineO::windowPtr = NULL;
int EngineO::screenWidth = 1280;
int EngineO::screenHeight = 720;

Timer EngineO::timer = Timer();
Shader EngineO::shader = Shader("shaders/vPhong.glsl", "shaders/fPhong.glsl");
Camera EngineO::camera = Camera();
Mesh EngineO::mesh = Mesh();
Light EngineO::light = Light();

bool EngineO::Start() {

	return true;
}

void EngineO::Update() {
}

void EngineO::HandleCameraInput() {
	//Camera location vector
	glm::vec3* cl = &EngineO::camera.loc;
	//Camera rotation vector
	glm::vec3* cr = &EngineO::camera.rot;

	glm::mat3 R = (glm::mat3)glm::yawPitchRoll((*cr).y, (*cr).x, (*cr).z);

	//Rotation sensitivity
	float hSens = 0.003; //Side to side
	float vSens = 0.003;  //Up and down
    
    //Mouse Input
	int w = EngineO::screenWidth, h = EngineO::screenHeight;
	double x, y;
	glfwGetCursorPos(EngineO::windowPtr, &x, &y);
	//Reference to the rotation matrix
	(*cr).y -= hSens * (x - w * 0.5f); //yaw
	(*cr).x -= vSens * (y - h * 0.5f); //pitch
	(*cr).x = glm::clamp((*cr).x, -0.5f*3.1415f, 0.5f*3.1415f);

	//Set cursor to center of window
	glfwSetCursorPos(EngineO::windowPtr, w*0.5f, h*0.5f);
	
	//Keyboard input
	glm::vec3 vel = EngineO::camera.vel;

	if (glfwGetKey(EngineO::windowPtr, GLFW_KEY_D)) {
		vel += R * glm::vec3(1, 0, 0);
	}
	if (glfwGetKey(EngineO::windowPtr, GLFW_KEY_A)) {
		vel += R * glm::vec3(-1, 0, 0);
	}
	if (glfwGetKey(EngineO::windowPtr, GLFW_KEY_W)) {
		vel += R * glm::vec3(0, 0, -1);
	}
	if (glfwGetKey(EngineO::windowPtr, GLFW_KEY_S)) {
		vel += R * glm::vec3(0, 0, 1);
	}
	if (glfwGetKey(EngineO::windowPtr, GLFW_KEY_R)) {
		vel += R * glm::vec3(0, 1, 0);
	}
	if (glfwGetKey(EngineO::windowPtr, GLFW_KEY_F)) {
		vel += R * glm::vec3(0, -1, 0);
	}

	float speed = 4.0f;
	if (vel != glm::vec3()) {
		EngineO::camera.vel = glm::normalize(vel) * speed * EngineO::timer.dt;
	}
}

void EngineO::Stop() {
	//Unload shaders
	shader.unload();

	//Terminate openGL
	glfwTerminate();
}
