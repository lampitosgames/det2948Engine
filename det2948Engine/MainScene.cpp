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

	Handle cubeMesh = RS->CreateMesh("models/box.obj");
	Handle cubeObj = OF->CreateGameObject<GameObject>("rotating cube");
	objects.push_back(cubeObj);
	OF->GiveMeshRenderer(cubeObj, cubeMesh);
	Handle shader = RS->CreateShader("shaders/vPhong.glsl", "shaders/fPhongColor.glsl");
	//Handle texture = RS->CreateTexture("images/metal.png");
	Handle materialHandle = RS->CreateMaterial(shader, vec3(1.0f, 0.0f, 0.0f));
	OF->Get<Material*>(materialHandle)->SetSpecular(8.0f);
	OF->GiveMaterial(cubeObj, materialHandle);
	Transform* cubeTransform = OF->Get<GameObject*>(cubeObj)->GetComponent<Transform*>(pType::TRANSFORM);
	cubeTransform->scale.y = 0.1f;
	cubeTransform->scale.x = 5.0f;
	cubeTransform->scale.z = 5.0f;
	cubeTransform->location.y = -2.0f;

	//Sphere object
	Handle sphereMesh = RS->CreateMesh("models/sphere.obj");
	Handle sphereObj = OF->CreateGameObject<BouncingBall>("sphere");
	objects.push_back(sphereObj);
	OF->GiveMeshRenderer(sphereObj, sphereMesh);
	OF->GiveRigidBody(sphereObj, 1.0f, 0.5f);
	OF->Get<BouncingBall*>(sphereObj)->GetComponent<Transform*>(pType::TRANSFORM)->location = vec3(0.05f, 35.0f, 0.01f);
	OF->Get<BouncingBall*>(sphereObj)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasGravity = true;
	OF->Get<BouncingBall*>(sphereObj)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasDrag = true;
	OF->GiveSphereCollider(sphereObj, 1.0f);

	Handle sphereObj2 = OF->CreateGameObject<BouncingBall>("sphere");
	objects.push_back(sphereObj2);
	OF->GiveMaterial(sphereObj2, materialHandle);
	OF->GiveMeshRenderer(sphereObj2, sphereMesh);
	OF->GiveRigidBody(sphereObj2, 2.0f, 0.3f);
	OF->Get<BouncingBall*>(sphereObj2)->GetComponent<Transform*>(pType::TRANSFORM)->location = vec3(0.05f, 30.0f, 0.01f);
	OF->Get<BouncingBall*>(sphereObj2)->GetComponent<Transform*>(pType::TRANSFORM)->scale = vec3(1.5f, 1.5f, 1.5f);
	OF->Get<BouncingBall*>(sphereObj2)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasGravity = true;
	OF->Get<BouncingBall*>(sphereObj2)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasDrag = true;
	OF->GiveSphereCollider(sphereObj2, 1.0f);

	Handle staticSphereObj = OF->CreateGameObject<BouncingBall>("staticSphere");
	objects.push_back(staticSphereObj);
	OF->GiveMeshRenderer(staticSphereObj, sphereMesh);
	OF->GiveRigidBody(staticSphereObj, 0.0f, 0.5f);
	OF->Get<BouncingBall*>(staticSphereObj)->GetComponent<Transform*>(pType::TRANSFORM)->location.y = 0.0f;
	OF->Get<BouncingBall*>(staticSphereObj)->GetComponent<Transform*>(pType::TRANSFORM)->scale = vec3(2.0f, 2.0f, 2.0f);
	OF->GiveSphereCollider(staticSphereObj, 1.0f);

	return true;
}

void MainScene::Update(float dt) {
	//Call parent
	Scene::Update(dt);
}
