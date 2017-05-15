#include "MainScene.h"
#include "Engine.h"
#include <string>
#include "GameObject.h"
#include "Camera.h"
#include "Transform.h"
#include "RigidBody.h"
#include "BouncingObj.h"
#include "MovableOOB.h"
#include "ObjectFactory.h"

using namespace std;

bool MainScene::Start() {
	OF = &Engine::OF;
	RS = &Engine::renderSys;
	PS = &Engine::physicsSys;

	Handle cubeMesh = RS->CreateMesh("models/box.obj");

	Handle colorShader = RS->CreateShader("shaders/vPhongColor.glsl", "shaders/fPhongColor.glsl");
	Handle floorMaterial = RS->CreateMaterial(colorShader, vec3(0.168627f, 0.176470f, 0.258823f));

	//CREATE OBJECTS
	//Create the camera
	RS->curCamera = OF->CreateGameObject<Camera>("MainCamera");
	OF->GiveRigidBody(Engine::renderSys.curCamera, 1.0f, 0.0f);
	OF->Get<GameObject*>(RS->curCamera)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasGravity = true;
	OF->Get<GameObject*>(RS->curCamera)->GetComponent<Transform*>(pType::TRANSFORM)->location.y = 6.0f;
	objects.push_back(RS->curCamera);
	OF->GiveAABBCollider(RS->curCamera, 2.0f, 3.0f, 2.0f);


	//Floor
	objects.push_back(OF->CreatePlatformObject(vec3(0.0f, 0.0f, 0.0f), vec3(100.0f, 1.0f, 100.0f), cubeMesh, floorMaterial));

	//wall1
	objects.push_back(OF->CreatePlatformObject(vec3(0.0f, 10.0f, -101.0f), vec3(102.0f, 10.0f, 1.0f), cubeMesh, floorMaterial));

	//wall2
	objects.push_back(OF->CreatePlatformObject(vec3(0.0f, 10.0f, 101.0f), vec3(102.0f, 10.0f, 1.0f), cubeMesh, floorMaterial));

	//wall3
	objects.push_back(OF->CreatePlatformObject(vec3(101.0f, 10.0f, 0.0f), vec3(1.0f, 10.0f, 102.0f), cubeMesh, floorMaterial));

	//wall4
	objects.push_back(OF->CreatePlatformObject(vec3(-101.0f, 10.0f, 0.0f), vec3(1.0f, 10.0f, 102.0f), cubeMesh, floorMaterial));

	//Platforms
	objects.push_back(OF->CreatePlatformObject(vec3(-13.0f, 3.0f, -10.0f), vec3(3.0f, 0.5f, 3.0f), cubeMesh, Handle()));
	objects.push_back(OF->CreatePlatformObject(vec3(-3.0f, 6.0f, -16.0f), vec3(3.0f, 0.5f, 3.0f), cubeMesh, Handle()));
	objects.push_back(OF->CreatePlatformObject(vec3(9.0f, 9.0f, -12.0f), vec3(3.0f, 0.5f, 3.0f), cubeMesh, Handle()));
	objects.push_back(OF->CreatePlatformObject(vec3(12.0f, 12.0f, 2.0f), vec3(3.0f, 0.5f, 3.0f), cubeMesh, Handle()));
	//Walls
	objects.push_back(OF->CreatePlatformObject(vec3(14.0f, 3.95f, 2.0f), vec3(0.5f, 3.0f, 5.0f), cubeMesh, Handle()));
	objects.push_back(OF->CreatePlatformObject(vec3(24.0f, 3.95f, 2.0f), vec3(0.5f, 3.0f, 5.0f), cubeMesh, Handle()));
	objects.push_back(OF->CreatePlatformObject(vec3(19.0f, 3.95f, 7.0f), vec3(5.0f, 3.0f, 0.5f), cubeMesh, Handle()));
	objects.push_back(OF->CreatePlatformObject(vec3(19.0f, 3.95f, -3.0f), vec3(5.0f, 3.0f, 0.5f), cubeMesh, Handle()));

	////Static sphere
	//Handle sphereMesh = RS->CreateMesh("models/sphere.obj");
	//Handle staticSphereObj = OF->CreateGameObject<BouncingObj>("staticSphere");
	//objects.push_back(staticSphereObj);
	//OF->GiveMeshRenderer(staticSphereObj, sphereMesh);
	//OF->GiveRigidBody(staticSphereObj, 0.0f, 0.5f);
	//OF->Get<BouncingObj*>(staticSphereObj)->GetComponent<Transform*>(pType::TRANSFORM)->location.y = 0.0f;
	//OF->Get<BouncingObj*>(staticSphereObj)->GetComponent<Transform*>(pType::TRANSFORM)->scale = vec3(2.0f, 2.0f, 2.0f);
	//OF->GiveSphereCollider(staticSphereObj, 1.0f);

	////Falling cubes
	//Handle fallingCube = OF->CreateGameObject<BouncingObj>("fallingCube");
	//objects.push_back(fallingCube);
	//OF->GiveMeshRenderer(fallingCube, cubeMesh);
	//OF->GiveRigidBody(fallingCube, 1.0f, 0.5f);
	//OF->Get<BouncingObj*>(fallingCube)->GetComponent<Transform*>(pType::TRANSFORM)->location = vec3(0.05f, 35.0f, 0.01f);
	//OF->Get<BouncingObj*>(fallingCube)->GetComponent<Transform*>(pType::TRANSFORM)->scale = vec3(0.1f, 3.0f, 0.3f);
	//OF->Get<BouncingObj*>(fallingCube)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasGravity = true;
	//OF->Get<BouncingObj*>(fallingCube)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasDrag = true;
	//OF->GiveAABBCollider(fallingCube, 2.0f, 2.0f, 2.0f);

	//Handle fallingCube2 = OF->CreateGameObject<BouncingObj>("fallingCube");
	//objects.push_back(fallingCube2);
	//OF->GiveMeshRenderer(fallingCube2, cubeMesh);
	//OF->GiveRigidBody(fallingCube2, 4.0f, 0.1f);
	//OF->Get<BouncingObj*>(fallingCube2)->GetComponent<Transform*>(pType::TRANSFORM)->location = vec3(0.5f, 10.0f, 0.01f);
	//OF->Get<BouncingObj*>(fallingCube2)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasGravity = true;
	//OF->Get<BouncingObj*>(fallingCube2)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasDrag = true;
	//OF->GiveAABBCollider(fallingCube2, 2.0f, 2.0f, 2.0f);

	//Handle fallingCube3 = OF->CreateGameObject<BouncingObj>("fallingCube");
	//objects.push_back(fallingCube3);
	//OF->GiveMeshRenderer(fallingCube3, cubeMesh);
	//OF->GiveRigidBody(fallingCube3, 2.0f, 0.6f);
	//OF->Get<BouncingObj*>(fallingCube3)->GetComponent<Transform*>(pType::TRANSFORM)->location = vec3(-2.0f, 40.0f, 0.0f);
	//OF->Get<BouncingObj*>(fallingCube3)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasGravity = true;
	//OF->Get<BouncingObj*>(fallingCube3)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasDrag = true;
	//OF->GiveAABBCollider(fallingCube3, 2.0f, 2.0f, 2.0f);


	////Falling spheres
	//Handle sphereObj = OF->CreateGameObject<BouncingObj>("sphere");
	//objects.push_back(sphereObj);
	//OF->GiveMeshRenderer(sphereObj, sphereMesh);
	//OF->GiveRigidBody(sphereObj, 1.0f, 0.6f);
	//OF->Get<BouncingObj*>(sphereObj)->GetComponent<Transform*>(pType::TRANSFORM)->location = vec3(0.05f, 20.0f, 0.01f);
	//OF->Get<BouncingObj*>(sphereObj)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasGravity = true;
	//OF->Get<BouncingObj*>(sphereObj)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasDrag = true;
	//OF->GiveSphereCollider(sphereObj, 1.0f);

	//Handle sphereObj2 = OF->CreateGameObject<BouncingObj>("sphere");
	//objects.push_back(sphereObj2);
	//OF->GiveMaterial(sphereObj2, redMaterial);
	//OF->GiveMeshRenderer(sphereObj2, sphereMesh);
	//OF->GiveRigidBody(sphereObj2, 2.0f, 0.3f);
	//OF->Get<BouncingObj*>(sphereObj2)->GetComponent<Transform*>(pType::TRANSFORM)->location = vec3(0.5f, 30.0f, 0.01f);
	//OF->Get<BouncingObj*>(sphereObj2)->GetComponent<Transform*>(pType::TRANSFORM)->scale = vec3(1.5f, 1.5f, 1.5f);
	//OF->Get<BouncingObj*>(sphereObj2)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasGravity = true;
	//OF->Get<BouncingObj*>(sphereObj2)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasDrag = true;
	//OF->GiveSphereCollider(sphereObj2, 1.0f);

	//Handle sphereObj3 = OF->CreateGameObject<BouncingObj>("sphere");
	//objects.push_back(sphereObj3);
	//OF->GiveMeshRenderer(sphereObj3, sphereMesh);
	//OF->GiveRigidBody(sphereObj3, 7.0f, 0.6f);
	//OF->Get<BouncingObj*>(sphereObj3)->GetComponent<Transform*>(pType::TRANSFORM)->location = vec3(3.0f, 10.0f, 1.0f);
	//OF->Get<BouncingObj*>(sphereObj3)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasGravity = true;
	//OF->Get<BouncingObj*>(sphereObj3)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasDrag = true;
	//OF->GiveSphereCollider(sphereObj3, 1.0f);

	//Handle sphereObj4 = OF->CreateGameObject<BouncingObj>("sphere");
	//objects.push_back(sphereObj4);
	//OF->GiveMeshRenderer(sphereObj4, sphereMesh);
	//OF->GiveRigidBody(sphereObj4, 4.0f, 0.2f);
	//OF->Get<BouncingObj*>(sphereObj4)->GetComponent<Transform*>(pType::TRANSFORM)->location = vec3(4.0f, 10.0f, -2.0f);
	//OF->Get<BouncingObj*>(sphereObj4)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasGravity = true;
	//OF->Get<BouncingObj*>(sphereObj4)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasDrag = true;
	//OF->GiveSphereCollider(sphereObj4, 1.0f);

	return true;
}

void MainScene::Update(float dt) {
	//Call parent
	Scene::Update(dt);
}
