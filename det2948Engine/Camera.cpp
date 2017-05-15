#include "Camera.h"
#include "Input.h"
#include "Transform.h"
#include "RigidBody.h"
#include "BouncingObj.h"
#include "Engine.h"

Camera::Camera() {
}

void Camera::Start() {
	ballMesh = Engine::renderSys.CreateMesh("models/sphere.obj");
	Handle colorShader = Engine::renderSys.CreateShader("shaders/vPhongColor.glsl", "shaders/fPhongColor.glsl");
	ballMat = Engine::renderSys.CreateMaterial(colorShader, vec3(0.937254f, 0.137254f, 0.235294f));
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

	if (Input::KeyUp(GLFW_MOUSE_BUTTON_1)) {
		ShootSphere();
	}
}

void Camera::HandleInput() {
	Transform* transf = GetComponent<Transform*>(pType::TRANSFORM);
	RigidBody* rigid = GetComponent<RigidBody*>(pType::RIGID_BODY);
	//Camera rotation vector
	glm::vec3* cr = &(transf->rotation);

	//Rotation sensitivity
	float hSens = 0.001; //Side to side
	float vSens = 0.001;  //Up and down
	glm::vec2 mPos = Input::MouseDelta();
	//Reference to the rotation matrix
	(*cr).y -= hSens * mPos.x; //yaw
	(*cr).x -= vSens * mPos.y; //pitch

	float speed = 40.0f;

	if (Input::Key(GLFW_KEY_D)) {
		rigid->ApplyForce((glm::mat3)yawPitchRoll(cr->y, 0.0f, 0.0f) * glm::vec3(1.0f, 0.0f, 0.0f) * speed);
	}
	if (Input::Key(GLFW_KEY_A)) {
		rigid->ApplyForce((glm::mat3)yawPitchRoll(cr->y, 0.0f, 0.0f) * glm::vec3(-1.0f, 0.0f, 0.0f) * speed);
	}
	if (Input::Key(GLFW_KEY_W)) {
		rigid->ApplyForce((glm::mat3)yawPitchRoll(cr->y, 0.0f, 0.0f) * glm::vec3(0.0f, 0.0f, -1.0f) * speed);
	}
	if (Input::Key(GLFW_KEY_S)) {
		rigid->ApplyForce((glm::mat3)yawPitchRoll(cr->y, 0.0f, 0.0f) * glm::vec3(0.0f, 0.0f, 1.0f) * speed);
	}
	if (Input::KeyDown(GLFW_KEY_SPACE)) {
		rigid->ApplyForce(glm::vec3(0.0f, 750.0f, 0.0f));
	}

	//Set drag on the ground
	//Don't apply negative vertical force
	glm::vec3 negForce = -4.0f * rigid->mass * rigid->vel;
	negForce.y = 0.0f;
	rigid->ApplyForce(negForce);
	//Give this object more gravity
	rigid->ApplyForce(vec3(0.0f, -4.0f, 0.0f));
}

void Camera::ShootSphere() {
	Handle bullet = Engine::OF.CreateGameObject<BouncingObj>("bullet");
	Engine::OF.GiveMaterial(bullet, ballMat);
	Engine::OF.GiveRigidBody(bullet, 1.0f, 0.5f);
	Engine::OF.GiveMeshRenderer(bullet, ballMesh);
	Engine::OF.GiveSphereCollider(bullet, 1.0f);
	BouncingObj* obj = Engine::OF.Get<BouncingObj*>(bullet);
	Transform* trans = obj->GetComponent<Transform*>(pType::TRANSFORM);
	RigidBody* rigid = obj->GetComponent<RigidBody*>(pType::RIGID_BODY);
	Transform* thisTrans = this->GetComponent<Transform*>(pType::TRANSFORM);
	RigidBody* thisRigid = this->GetComponent<RigidBody*>(pType::RIGID_BODY);

	trans->location = thisTrans->location + (thisTrans->Forward() * -2.0f);
	trans->scale = vec3(0.5f, 0.5f, 0.5f);
	rigid->hasGravity = true;
	rigid->ApplyForce(thisTrans->Forward() * rigid->mass * -1500.0f);

	obj->SetActive(true);
}
