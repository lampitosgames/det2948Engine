#include "MainScene.h"
#include "Engine.h"
#include <string>
#include "GameObject.h"
#include "Camera.h"
#include "Transform.h"
#include "RigidBody.h"
#include "BouncingBallObj.h"
#include "ObjectFactory.h"

using namespace std;

bool MainScene::Start() {
	OF = &Engine::OF;
	RS = &Engine::renderSys;
	PS = &Engine::physicsSys;

	//CREATE OBJECTS
	//Create the camera
	RS->curCamera = OF->CreateGameObject<Camera>("MainCamera");
	OF->GiveRigidBody(Engine::renderSys.curCamera, 0.0f);
	OF->Get<GameObject*>(RS->curCamera)->GetComponent<Transform*>(pType::TRANSFORM)->location.z = 6.0f;

	objects.push_back(RS->curCamera);

	//Create a mesh - creation order matters.  second one breaks the handle
	Handle sphereMesh = RS->CreateMesh("models/sphere.obj");
	Handle cubeMesh = RS->CreateMesh("models/box.obj");

	//Create a game object
	Handle rotatingCube = OF->CreateGameObject<GameObject>("rotating cube");
	Handle sphereObj = OF->CreateGameObject<BouncingBall>("sphere");
	objects.push_back(rotatingCube);
	objects.push_back(sphereObj);

	//Give the sphere object a mesh renderer
	OF->GiveMeshRenderer(sphereObj, sphereMesh);
	OF->GiveMeshRenderer(rotatingCube, cubeMesh);

	Handle shader = RS->CreateShader("shaders/vPhong.glsl", "shaders/fPhong.glsl");
	Handle texture = RS->CreateTexture("images/metal.png");
	Handle materialHandle = RS->CreateMaterial(texture, shader);

	OF->GiveMaterial(rotatingCube, materialHandle);

	Transform* cubeTransform = OF->Get<GameObject*>(rotatingCube)->GetComponent<Transform*>(pType::TRANSFORM);
	cubeTransform->scale.y = 0.1f;
	cubeTransform->scale.x = 5.0f;
	cubeTransform->scale.z = 5.0f;
	cubeTransform->location.y = -2.0f;

	OF->GiveRigidBody(sphereObj, 3.0f);
	OF->Get<BouncingBall*>(sphereObj)->GetComponent<Transform*>(pType::TRANSFORM)->location.y = 30.0f;
	OF->Get<BouncingBall*>(sphereObj)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasGravity = true;
	OF->Get<BouncingBall*>(sphereObj)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasDrag = true;
	return true;
}

void MainScene::Update(float dt) {
	//Call parent
	Scene::Update(dt);
}
