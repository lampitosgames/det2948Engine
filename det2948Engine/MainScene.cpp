#include "MainScene.h"
#include "Engine.h"
#include <string>
#include "GameObject.h"
#include "Camera.h"
#include "Transform.h"
#include "RigidBody.h"
#include "BouncingObj.h"
#include "ObjectFactory.h"

using namespace std;

bool MainScene::Start() {
	OF = &Engine::OF;
	RS = &Engine::renderSys;
	PS = &Engine::physicsSys;

	Handle shader = RS->CreateShader("shaders/vPhong.glsl", "shaders/fPhong.glsl");
	Handle texture = RS->CreateTexture("images/metal.png");
	Handle metalMaterial = RS->CreateMaterial(texture, shader);

	Handle colorShader = RS->CreateShader("shaders/vPhongColor.glsl", "shaders/fPhongColor.glsl");
	Handle redMaterial = RS->CreateMaterial(colorShader, vec3(0.5f, 0.25f, 0.25f));

	//CREATE OBJECTS
	//Create the camera
	RS->curCamera = OF->CreateGameObject<Camera>("MainCamera");
	OF->GiveRigidBody(Engine::renderSys.curCamera, 0.0f, 0.0f);
	OF->Get<GameObject*>(RS->curCamera)->GetComponent<Transform*>(pType::TRANSFORM)->location.z = 6.0f;
	objects.push_back(RS->curCamera);
	OF->GiveAABBCollider(RS->curCamera, 2.0f, 2.0f, 2.0f);

	//Floor
	Handle cubeMesh = RS->CreateMesh("models/box.obj");
	Handle cubeObj = OF->CreateGameObject<GameObject>("rotating cube");
	objects.push_back(cubeObj);
	OF->GiveMeshRenderer(cubeObj, cubeMesh);
	OF->GiveRigidBody(cubeObj, 0.0f);
	OF->Get<Material*>(metalMaterial)->SetSpecular(2.0f);
	OF->GiveMaterial(cubeObj, metalMaterial);
	Transform* cubeTransform = OF->Get<GameObject*>(cubeObj)->GetComponent<Transform*>(pType::TRANSFORM);
	cubeTransform->scale.y = 1.0f;
	cubeTransform->scale.x = 10.0f;
	cubeTransform->scale.z = 10.0f;
	cubeTransform->location.y = -2.0f;
	OF->GiveAABBCollider(cubeObj, 2.0f, 2.0f, 2.0f);
	//wall1
	Handle wall1 = OF->CreateGameObject<GameObject>("wall1");
	objects.push_back(wall1);
	OF->GiveMeshRenderer(wall1, cubeMesh);
	OF->GiveRigidBody(wall1, 0.0f);
	OF->GiveMaterial(wall1, metalMaterial);
	Transform* wall1trans = OF->Get<GameObject*>(wall1)->GetComponent<Transform*>(pType::TRANSFORM);
	wall1trans->scale = vec3(1.0f, 4.0f, 10.0f);
	wall1trans->location = vec3(-11.0f, 2.0f, 0.0f);
	OF->GiveAABBCollider(wall1, 2.0f, 2.0f, 2.0f);
	//wall2
	Handle wall2 = OF->CreateGameObject<GameObject>("wall1");
	objects.push_back(wall2);
	OF->GiveMeshRenderer(wall2, cubeMesh);
	OF->GiveRigidBody(wall2, 0.0f);
	OF->GiveMaterial(wall2, metalMaterial);
	Transform* wall2trans = OF->Get<GameObject*>(wall2)->GetComponent<Transform*>(pType::TRANSFORM);
	wall2trans->scale = vec3(1.0f, 4.0f, 10.0f);
	wall2trans->location = vec3(11.0f, 2.0f, 0.0f);
	OF->GiveAABBCollider(wall2, 2.0f, 2.0f, 2.0f);
	//wall3
	Handle wall3 = OF->CreateGameObject<GameObject>("wall1");
	objects.push_back(wall3);
	OF->GiveMeshRenderer(wall3, cubeMesh);
	OF->GiveRigidBody(wall3, 0.0f);
	OF->GiveMaterial(wall3, metalMaterial);
	Transform* wall3trans = OF->Get<GameObject*>(wall3)->GetComponent<Transform*>(pType::TRANSFORM);
	wall3trans->scale = vec3(10.0f, 4.0f, 1.0f);
	wall3trans->location = vec3(0.0f, 2.0f, -11.0f);
	OF->GiveAABBCollider(wall3, 2.0f, 2.0f, 2.0f);
	//wall4
	Handle wall4 = OF->CreateGameObject<GameObject>("wall1");
	objects.push_back(wall4);
	OF->GiveMeshRenderer(wall4, cubeMesh);
	OF->GiveRigidBody(wall4, 0.0f);
	OF->GiveMaterial(wall4, metalMaterial);
	Transform* wall4trans = OF->Get<GameObject*>(wall4)->GetComponent<Transform*>(pType::TRANSFORM);
	wall4trans->scale = vec3(10.0f, 4.0f, 1.0f);
	wall4trans->location = vec3(0.0f, 2.0f, 11.0f);
	OF->GiveAABBCollider(wall4, 2.0f, 2.0f, 2.0f);
	//Static sphere
	Handle sphereMesh = RS->CreateMesh("models/sphere.obj");
	Handle staticSphereObj = OF->CreateGameObject<BouncingObj>("staticSphere");
	objects.push_back(staticSphereObj);
	OF->GiveMeshRenderer(staticSphereObj, sphereMesh);
	OF->GiveRigidBody(staticSphereObj, 0.0f, 0.5f);
	OF->Get<BouncingObj*>(staticSphereObj)->GetComponent<Transform*>(pType::TRANSFORM)->location.y = 0.0f;
	OF->Get<BouncingObj*>(staticSphereObj)->GetComponent<Transform*>(pType::TRANSFORM)->scale = vec3(2.0f, 2.0f, 2.0f);
	OF->GiveSphereCollider(staticSphereObj, 1.0f);

	//Falling cubes
	Handle fallingCube = OF->CreateGameObject<BouncingObj>("fallingCube");
	objects.push_back(fallingCube);
	OF->GiveMeshRenderer(fallingCube, cubeMesh);
	OF->GiveRigidBody(fallingCube, 1.0f, 0.5f);
	OF->Get<BouncingObj*>(fallingCube)->GetComponent<Transform*>(pType::TRANSFORM)->location = vec3(0.05f, 35.0f, 0.01f);
	OF->Get<BouncingObj*>(fallingCube)->GetComponent<Transform*>(pType::TRANSFORM)->scale = vec3(0.1f, 3.0f, 0.3f);
	OF->Get<BouncingObj*>(fallingCube)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasGravity = true;
	OF->Get<BouncingObj*>(fallingCube)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasDrag = true;
	OF->GiveAABBCollider(fallingCube, 2.0f, 2.0f, 2.0f);

	Handle fallingCube2 = OF->CreateGameObject<BouncingObj>("fallingCube");
	objects.push_back(fallingCube2);
	OF->GiveMeshRenderer(fallingCube2, cubeMesh);
	OF->GiveRigidBody(fallingCube2, 4.0f, 0.1f);
	OF->Get<BouncingObj*>(fallingCube2)->GetComponent<Transform*>(pType::TRANSFORM)->location = vec3(0.5f, 10.0f, 0.01f);
	OF->Get<BouncingObj*>(fallingCube2)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasGravity = true;
	OF->Get<BouncingObj*>(fallingCube2)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasDrag = true;
	OF->GiveAABBCollider(fallingCube2, 2.0f, 2.0f, 2.0f);

	Handle fallingCube3 = OF->CreateGameObject<BouncingObj>("fallingCube");
	objects.push_back(fallingCube3);
	OF->GiveMeshRenderer(fallingCube3, cubeMesh);
	OF->GiveRigidBody(fallingCube3, 2.0f, 0.9f);
	OF->Get<BouncingObj*>(fallingCube3)->GetComponent<Transform*>(pType::TRANSFORM)->location = vec3(-2.0f, 40.0f, 0.0f);
	OF->Get<BouncingObj*>(fallingCube3)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasGravity = true;
	OF->Get<BouncingObj*>(fallingCube3)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasDrag = true;
	OF->GiveAABBCollider(fallingCube3, 2.0f, 2.0f, 2.0f);


	//Falling spheres
	Handle sphereObj = OF->CreateGameObject<BouncingObj>("sphere");
	objects.push_back(sphereObj);
	OF->GiveMeshRenderer(sphereObj, sphereMesh);
	OF->GiveRigidBody(sphereObj, 1.0f, 0.9f);
	OF->Get<BouncingObj*>(sphereObj)->GetComponent<Transform*>(pType::TRANSFORM)->location = vec3(0.05f, 20.0f, 0.01f);
	OF->Get<BouncingObj*>(sphereObj)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasGravity = true;
	OF->Get<BouncingObj*>(sphereObj)->GetComponent<RigidBody*>(pType::RIGID_BODY)->hasDrag = true;
	OF->GiveSphereCollider(sphereObj, 1.0f);

	Handle sphereObj2 = OF->CreateGameObject<BouncingObj>("sphere");
	objects.push_back(sphereObj2);
	OF->GiveMaterial(sphereObj2, redMaterial);
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
}
