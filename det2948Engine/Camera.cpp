#include "Camera.h"
#include "Input.h"
#include "Transform.h"
#include "RigidBody.h"

Camera::Camera() {
}

void Camera::Start() {
}

void Camera::Update() {
	Transform* transf = this->GetComponent<Transform*>(pType::TRANSFORM);
	//Update matrices based on current attributes
	mat3 rotMat = transf->rotMatrix();
	//Get the lookAt matrix
	//The position of the camera's view
	vec3 eye = transf->location;
	//Where the camera is pointed (where it's 'centered on')
	vec3 center = eye + rotMat*vec3(0, 0, -1);
	//Defines the upwards direction by rotating a unit vector by the rotation matrix
	vec3 up = rotMat * vec3(0, 1, 0);
	this->lookAtMatrix = lookAt(eye, center, up);

	//Get the projection matrix (projects from a frustum)
	this->projMatrix = perspective(this->fov, this->aspectRatio, this->near, this->far);

	//Finally, get the camera matrix
	this->camMatrix = this->projMatrix * this->lookAtMatrix;

	HandleInput();
}

void Camera::HandleInput() {
	Transform* transf = GetComponent<Transform*>(pType::TRANSFORM);
	//Camera location vector
	glm::vec3* cl = &(transf->location);
	//Camera rotation vector
	glm::vec3* cr = &(transf->rotation);

	glm::mat3 R = transf->rotMatrix();

	//Rotation sensitivity
	float hSens = 0.001; //Side to side
	float vSens = 0.001;  //Up and down
	glm::vec2 mPos = Input::MouseDelta();
	//Reference to the rotation matrix
	(*cr).y -= hSens * mPos.x; //yaw
	(*cr).x -= vSens * mPos.y; //pitch

							   //Keyboard input
	glm::vec3 vel = glm::vec3(0.0f, 0.0f, 0.0f);

	if (Input::Key(GLFW_KEY_D)) {
		vel += R * glm::vec3(1, 0, 0);
	}
	if (Input::Key(GLFW_KEY_A)) {
		vel += R * glm::vec3(-1, 0, 0);
	}
	if (Input::Key(GLFW_KEY_W)) {
		vel += R * glm::vec3(0, 0, -1);
	}
	if (Input::Key(GLFW_KEY_S)) {
		vel += R * glm::vec3(0, 0, 1);
	}
	if (Input::Key(GLFW_KEY_R)) {
		vel += R * glm::vec3(0, 1, 0);
	}
	if (Input::Key(GLFW_KEY_F)) {
		vel += R * glm::vec3(0, -1, 0);
	}

	float speed = 4.0f;
	if (vel != glm::vec3()) {
		GetComponent<RigidBody*>(pType::RIGID_BODY)->vel = glm::normalize(vel) * speed;
	}
	else {
		GetComponent<RigidBody*>(pType::RIGID_BODY)->vel = glm::vec3(0.0f, 0.0f, 0.0f);
	}
}
