#include "MainScene.h"
#include "Engine.h"
#include <string>
#include "GameObject.h"
#include "Camera.h"
#include "Transform.h"
#include "RigidBody.h"
#include "BouncingObj.h"
#include "RotatingPlatform.h"
#include "ObjectFactory.h"

using namespace std;

bool MainScene::Start() {
	OF = &Engine::OF;
	RS = &Engine::renderSys;
	PS = &Engine::physicsSys;

	Handle cubeMesh = RS->CreateMesh("models/box.obj");
	Handle sphereMesh = RS->CreateMesh("models/sphere.obj");

	Handle colorShader = RS->CreateShader("shaders/vPhongColor.glsl", "shaders/fPhongColor.glsl");
	Handle floorMaterial = RS->CreateMaterial(colorShader, vec3(0.168627f, 0.176470f, 0.258823f));
	Handle lightBlueMaterial = RS->CreateMaterial(colorShader, vec3(0.552941f, 0.6f, 0.682352f));
	Handle brightBlueMaterial = RS->CreateMaterial(colorShader, vec3(0.137254f, 0.643137f, 0.768627f));
	Handle yellowMaterial = RS->CreateMaterial(colorShader, vec3(0.976470f, 0.862745f, 0.360784f));
	Handle greenMaterial = RS->CreateMaterial(colorShader, vec3(0.513725f, 0.721568f, 0.231372f));

	//CREATE OBJECTS
	//Create the camera
	RS->curCamera = OF->CreateGameObject<Camera>("MainCamera");
	OF->GiveRigidBody(Engine::renderSys.curCamera, 1.0f, 0.0f);
	OF->Get<GameObject*>(RS->curCamera)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasGravity = true;
	OF->Get<GameObject*>(RS->curCamera)->GetComponent<Transform*>(pType::TRANSFORM)->location = vec3(0.0f, 6.0f, 6.0f);
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
	objects.push_back(OF->CreatePlatformObject(vec3(-13.0f, 3.0f, -10.0f), vec3(3.0f, 0.5f, 3.0f), cubeMesh, lightBlueMaterial));
	objects.push_back(OF->CreatePlatformObject(vec3(-3.0f, 6.0f, -16.0f), vec3(3.0f, 0.5f, 3.0f), cubeMesh, lightBlueMaterial));
	objects.push_back(OF->CreatePlatformObject(vec3(9.0f, 9.0f, -12.0f), vec3(3.0f, 0.5f, 3.0f), cubeMesh, lightBlueMaterial));
	objects.push_back(OF->CreatePlatformObject(vec3(12.0f, 12.0f, 2.0f), vec3(3.0f, 0.5f, 3.0f), cubeMesh, lightBlueMaterial));
	//Walls
	objects.push_back(OF->CreatePlatformObject(vec3(14.0f, 3.95f, 2.0f), vec3(0.5f, 3.0f, 5.0f), cubeMesh, lightBlueMaterial));
	objects.push_back(OF->CreatePlatformObject(vec3(24.0f, 3.95f, 2.0f), vec3(0.5f, 3.0f, 5.0f), cubeMesh, lightBlueMaterial));
	objects.push_back(OF->CreatePlatformObject(vec3(19.0f, 3.95f, 7.0f), vec3(5.0f, 3.0f, 0.5f), cubeMesh, lightBlueMaterial));
	objects.push_back(OF->CreatePlatformObject(vec3(19.0f, 3.95f, -3.0f), vec3(5.0f, 3.0f, 0.5f), cubeMesh, lightBlueMaterial));

	objects.push_back(OF->CreatePlatformObject(vec3(-25.89f, 6.0f, 16.11f), vec3(3.0f, 5.0f, 3.0f), cubeMesh, brightBlueMaterial));
	objects.push_back(OF->CreatePlatformObject(vec3(32.0f, 6.0f, 48.0f), vec3(3.0f, 5.0f, 6.0f), cubeMesh, brightBlueMaterial));
	objects.push_back(OF->CreatePlatformObject(vec3(24.0f, 7.5f, 48.0f), vec3(3.0f, 0.5f, 6.0f), cubeMesh, brightBlueMaterial));
	objects.push_back(OF->CreatePlatformObject(vec3(16.0f, 4.5f, 48.0f), vec3(3.0f, 0.5f, 6.0f), cubeMesh, brightBlueMaterial));
	objects.push_back(OF->CreatePlatformObject(vec3(8.0f, 1.5f, 48.0f), vec3(3.0f, 0.5f, 6.0f), cubeMesh, brightBlueMaterial));

	objects.push_back(OF->CreatePlatformObject(vec3(-33.0f, 10.5f, -51.0f), vec3(6.0f, 0.5f, 6.0f), cubeMesh, brightBlueMaterial));
	objects.push_back(OF->CreatePlatformObject(vec3(-33.0f, 1.5f, -24.0f), vec3(6.0f, 0.5f, 3.0f), cubeMesh, brightBlueMaterial));
	objects.push_back(OF->CreatePlatformObject(vec3(-33.0f, 4.5f, -32.0f), vec3(6.0f, 0.5f, 3.0f), cubeMesh, Handle()));
	objects.push_back(OF->CreatePlatformObject(vec3(-33.0f, 7.5f, -40.0f), vec3(6.0f, 0.5f, 3.0f), cubeMesh, lightBlueMaterial));
	objects.push_back(OF->CreatePlatformObject(vec3(-33.0f, 7.5f, -62.0f), vec3(6.0f, 0.5f, 3.0f), cubeMesh, lightBlueMaterial));
	objects.push_back(OF->CreatePlatformObject(vec3(-33.0f, 4.5f, -70.0f), vec3(6.0f, 0.5f, 3.0f), cubeMesh, Handle()));
	objects.push_back(OF->CreatePlatformObject(vec3(-33.0f, 1.5f, -78.0f), vec3(6.0f, 0.5f, 3.0f), cubeMesh, brightBlueMaterial));

	objects.push_back(OF->CreatePlatformObject(vec3(-60.0f, 1.5f, -51.0f), vec3(3.0f, 0.5f, 6.0f), cubeMesh, brightBlueMaterial));
	objects.push_back(OF->CreatePlatformObject(vec3(-52.0f, 4.5f, -51.0f), vec3(3.0f, 0.5f, 6.0f), cubeMesh, Handle()));
	objects.push_back(OF->CreatePlatformObject(vec3(-44.0f, 7.5f, -51.0f), vec3(3.0f, 0.5f, 6.0f), cubeMesh, lightBlueMaterial));
	objects.push_back(OF->CreatePlatformObject(vec3(-22.0f, 7.5f, -51.0f), vec3(3.0f, 0.5f, 6.0f), cubeMesh, lightBlueMaterial));
	objects.push_back(OF->CreatePlatformObject(vec3(-14.0f, 4.5f, -51.0f), vec3(3.0f, 0.5f, 6.0f), cubeMesh, Handle()));
	objects.push_back(OF->CreatePlatformObject(vec3(-6.0f, 1.5f, -51.0f), vec3(3.0f, 0.5f, 6.0f), cubeMesh, brightBlueMaterial));

	//Platform
	rotatingPlatform = OF->CreateGameObject<RotatingPlatform>("fallingCube");
	objects.push_back(rotatingPlatform);
	OF->GiveMeshRenderer(rotatingPlatform, cubeMesh);
	OF->GiveMaterial(rotatingPlatform, greenMaterial);
	OF->GiveRigidBody(rotatingPlatform, 0.0f);
	OF->Get<RotatingPlatform*>(rotatingPlatform)->GetComponent<Transform*>(pType::TRANSFORM)->location = vec3(45.0f, 15.0f, 0.0f);
	OF->Get<RotatingPlatform*>(rotatingPlatform)->GetComponent<Transform*>(pType::TRANSFORM)->scale = vec3(8.0f, 0.5f, 8.0f);
	OF->GiveAABBCollider(rotatingPlatform, 2.0f, 2.0f, 2.0f);

	rotatingPlatform2 = OF->CreateGameObject<RotatingPlatform>("fallingCube");
	objects.push_back(rotatingPlatform2);
	OF->GiveMeshRenderer(rotatingPlatform2, cubeMesh);
	OF->GiveMaterial(rotatingPlatform2, greenMaterial);
	OF->GiveRigidBody(rotatingPlatform2, 0.0f);
	OF->Get<RotatingPlatform*>(rotatingPlatform2)->GetComponent<Transform*>(pType::TRANSFORM)->location = vec3(45.0f, 23.0f, 0.0f);
	OF->Get<RotatingPlatform*>(rotatingPlatform2)->GetComponent<Transform*>(pType::TRANSFORM)->scale = vec3(5.0f, 0.5f, 5.0f);
	OF->GiveAABBCollider(rotatingPlatform2, 2.0f, 2.0f, 2.0f);

	//Static sphere
	Handle staticSphereObj = OF->CreateGameObject<GameObject>("staticSphere");
	objects.push_back(staticSphereObj);
	OF->GiveMeshRenderer(staticSphereObj, sphereMesh);
	OF->GiveMaterial(staticSphereObj, yellowMaterial);
	OF->GiveRigidBody(staticSphereObj, 0.0f, 0.5f);
	OF->Get<GameObject*>(staticSphereObj)->GetComponent<Transform*>(pType::TRANSFORM)->location.y = 0.0f;
	OF->Get<GameObject*>(staticSphereObj)->GetComponent<Transform*>(pType::TRANSFORM)->scale = vec3(2.0f, 2.0f, 2.0f);
	OF->GiveSphereCollider(staticSphereObj, 1.0f);

	Handle staticSphereObj0 = OF->CreateGameObject<GameObject>("staticSphere");
	objects.push_back(staticSphereObj0);
	OF->GiveMeshRenderer(staticSphereObj0, sphereMesh);
	OF->GiveMaterial(staticSphereObj0, yellowMaterial);
	OF->GiveRigidBody(staticSphereObj0, 0.0f, 0.5f);
	OF->Get<GameObject*>(staticSphereObj0)->GetComponent<Transform*>(pType::TRANSFORM)->location = vec3(0.0f, 8.0f, 35.0f);
	OF->Get<GameObject*>(staticSphereObj0)->GetComponent<Transform*>(pType::TRANSFORM)->scale = vec3(2.0f, 2.0f, 2.0f);
	OF->GiveSphereCollider(staticSphereObj0, 1.0f);

	Handle staticSphereObj1 = OF->CreateGameObject<GameObject>("staticSphere");
	objects.push_back(staticSphereObj1);
	OF->GiveMeshRenderer(staticSphereObj1, sphereMesh);
	OF->GiveMaterial(staticSphereObj1, yellowMaterial);
	OF->GiveRigidBody(staticSphereObj1, 0.0f, 0.5f);
	OF->Get<GameObject*>(staticSphereObj1)->GetComponent<Transform*>(pType::TRANSFORM)->location = vec3(-35.0f, 8.0f, 0.0f);
	OF->Get<GameObject*>(staticSphereObj1)->GetComponent<Transform*>(pType::TRANSFORM)->scale = vec3(2.0f, 2.0f, 2.0f);
	OF->GiveSphereCollider(staticSphereObj1, 1.0f);

	Handle staticSphereObj2 = OF->CreateGameObject<GameObject>("staticSphere");
	objects.push_back(staticSphereObj2);
	OF->GiveMeshRenderer(staticSphereObj2, sphereMesh);
	OF->GiveMaterial(staticSphereObj2, yellowMaterial);
	OF->GiveRigidBody(staticSphereObj2, 0.0f, 0.5f);
	OF->Get<GameObject*>(staticSphereObj2)->GetComponent<Transform*>(pType::TRANSFORM)->location = vec3(35.0f, 8.0f, 0.0f);
	OF->Get<GameObject*>(staticSphereObj2)->GetComponent<Transform*>(pType::TRANSFORM)->scale = vec3(2.0f, 2.0f, 2.0f);
	OF->GiveSphereCollider(staticSphereObj2, 1.0f);

	Handle staticSphereObj3 = OF->CreateGameObject<GameObject>("staticSphere");
	objects.push_back(staticSphereObj3);
	OF->GiveMeshRenderer(staticSphereObj3, sphereMesh);
	OF->GiveMaterial(staticSphereObj3, yellowMaterial);
	OF->GiveRigidBody(staticSphereObj3, 0.0f, 0.5f);
	OF->Get<GameObject*>(staticSphereObj3)->GetComponent<Transform*>(pType::TRANSFORM)->location = vec3(0.0f, 8.0f, -35.0f);
	OF->Get<GameObject*>(staticSphereObj3)->GetComponent<Transform*>(pType::TRANSFORM)->scale = vec3(2.0f, 2.0f, 2.0f);
	OF->GiveSphereCollider(staticSphereObj3, 1.0f);

	Handle staticSphereObj4 = OF->CreateGameObject<GameObject>("staticSphere");
	objects.push_back(staticSphereObj4);
	OF->GiveMeshRenderer(staticSphereObj4, sphereMesh);
	OF->GiveMaterial(staticSphereObj4, yellowMaterial);
	OF->GiveRigidBody(staticSphereObj4, 0.0f, 0.5f);
	OF->Get<GameObject*>(staticSphereObj4)->GetComponent<Transform*>(pType::TRANSFORM)->location = vec3(-33.0f, 10.5f, -51.0f);
	OF->Get<GameObject*>(staticSphereObj4)->GetComponent<Transform*>(pType::TRANSFORM)->scale = vec3(3.0f, 3.0f, 3.0f);
	OF->GiveSphereCollider(staticSphereObj4, 1.0f);

	
	//Falling spheres
	Handle sphereObj = OF->CreateGameObject<BouncingObj>("sphere");
	objects.push_back(sphereObj);
	OF->GiveMeshRenderer(sphereObj, sphereMesh);
	OF->GiveRigidBody(sphereObj, 1.0f, 0.6f);
	OF->Get<BouncingObj*>(sphereObj)->GetComponent<Transform*>(pType::TRANSFORM)->location = vec3(0.05f, 20.0f, 0.01f);
	OF->Get<BouncingObj*>(sphereObj)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasGravity = true;
	OF->Get<BouncingObj*>(sphereObj)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasDrag = true;
	OF->GiveSphereCollider(sphereObj, 1.0f);

	Handle sphereObj2 = OF->CreateGameObject<BouncingObj>("sphere");
	objects.push_back(sphereObj2);
	OF->GiveMaterial(sphereObj2, Handle());
	OF->GiveMeshRenderer(sphereObj2, sphereMesh);
	OF->GiveRigidBody(sphereObj2, 2.0f, 0.3f);
	OF->Get<BouncingObj*>(sphereObj2)->GetComponent<Transform*>(pType::TRANSFORM)->location = vec3(0.5f, 30.0f, 0.01f);
	OF->Get<BouncingObj*>(sphereObj2)->GetComponent<Transform*>(pType::TRANSFORM)->scale = vec3(1.5f, 1.5f, 1.5f);
	OF->Get<BouncingObj*>(sphereObj2)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasGravity = true;
	OF->Get<BouncingObj*>(sphereObj2)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasDrag = true;
	OF->GiveSphereCollider(sphereObj2, 1.0f);

	Handle sphereObj3 = OF->CreateGameObject<BouncingObj>("sphere");
	objects.push_back(sphereObj3);
	OF->GiveMeshRenderer(sphereObj3, sphereMesh);
	OF->GiveRigidBody(sphereObj3, 7.0f, 0.6f);
	OF->Get<BouncingObj*>(sphereObj3)->GetComponent<Transform*>(pType::TRANSFORM)->location = vec3(3.0f, 10.0f, 1.0f);
	OF->Get<BouncingObj*>(sphereObj3)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasGravity = true;
	OF->Get<BouncingObj*>(sphereObj3)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasDrag = true;
	OF->GiveSphereCollider(sphereObj3, 1.0f);

	Handle sphereObj4 = OF->CreateGameObject<BouncingObj>("sphere");
	objects.push_back(sphereObj4);
	OF->GiveMeshRenderer(sphereObj4, sphereMesh);
	OF->GiveRigidBody(sphereObj4, 4.0f, 0.2f);
	OF->Get<BouncingObj*>(sphereObj4)->GetComponent<Transform*>(pType::TRANSFORM)->location = vec3(4.0f, 10.0f, -2.0f);
	OF->Get<BouncingObj*>(sphereObj4)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasGravity = true;
	OF->Get<BouncingObj*>(sphereObj4)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasDrag = true;
	OF->GiveSphereCollider(sphereObj4, 1.0f);

	return true;
}

void MainScene::Update(float dt) {
	//Call parent
	Scene::Update(dt);

	Transform* trans = OF->Get<RotatingPlatform*>(rotatingPlatform)->GetComponent<Transform*>(pType::TRANSFORM);
	Transform* trans2 = OF->Get<RotatingPlatform*>(rotatingPlatform2)->GetComponent<Transform*>(pType::TRANSFORM);
	theta += 0.0872665f * dt;
	trans->location = vec3(cos(theta)*45.0f, trans->location.y, sin(theta)*45.0f);
	trans2->location = vec3(cos(-theta)*45.0f, trans2->location.y, sin(-theta)*45.0f);
}
