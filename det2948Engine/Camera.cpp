#include "Camera.h"
#include <FreeImage.h>

#include <GL\glew.h>	// The order
#include <GLFW\glfw3.h> // Of these matters

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>
#include "EngineO.h"

using namespace glm;

Camera::Camera() {

	//Set cursor to center of window
	glfwSetCursorPos(EngineO::windowPtr, EngineO::screenWidth*0.5f, EngineO::screenHeight*0.5f);
}

void Camera::Update() {
	this->loc += this->vel;
	this->vel = vec3(0, 0, 0);
	//Update matrices based on current attributes
	//TODO: Dont update unless things have changed
	mat3 rotMat = (mat3)yawPitchRoll(this->rot.y, this->rot.x, this->rot.z);

	//Get the lookAt matrix
	//The position of the camera's view
	vec3 eye = this->loc;
	//Where the camera is pointed (where it's 'centered on')
	vec3 center = eye + rotMat*vec3(0, 0, -1);
	//Defines the upwards direction by rotating a unit vector by the rotation matrix
	vec3 up = rotMat * vec3(0, 1, 0);
	this->lookAtMatrix = lookAt(eye, center, up);

	//Get the projection matrix (projects from a frustum)
	this->projMatrix = perspective(this->fov, this->aspectRatio, this->near, this->far);

	//Finally, get the camera matrix
	this->camMatrix = this->projMatrix * this->lookAtMatrix;

}
