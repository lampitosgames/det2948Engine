#include "ObjectFactory.h"
#include "Transform.h"
#include "MeshRender.h"
#include "Engine.h"


ObjectFactory::~ObjectFactory() {
	for (int i = 0; i < gameObjects.size(); i++) {
		delete gameObjects[i];
	}
}

bool ObjectFactory::Start() {
	//CREATE OBJECTS
	//Create the camera
	Engine::renderSys.curCamera = Engine::OF.CreateGameObject<Camera>("MainCamera");
	//Create a mesh - creation order matters.  second one breaks the handle
	sphereMesh = Engine::renderSys.CreateMesh("models/sphere.obj");
	cubeMesh = Engine::renderSys.CreateMesh("models/box.obj");

	Mesh* spherePtrFromHandle = Get<Mesh*>(sphereMesh);
	Mesh* cubePtrFromHandle = Get<Mesh*>(cubeMesh);

	Mesh* spherePtrFromArray = &Engine::renderSys.meshes[0];
	Mesh* cubePtrFromArray = &Engine::renderSys.meshes[1];

	//Create a game object
	cubeObj = CreateGameObject<GameObject>("cube");
	sphereObj = CreateGameObject<GameObject>("sphere");
	//Give the sphere object a mesh renderer
	GiveMeshRenderer(sphereObj, sphereMesh);
	GiveMeshRenderer(cubeObj, cubeMesh);

	//Move one of them 3 points in the positive x direction
	Get<GameObject*>(sphereObj)->GetComponent<Transform*>(pType::TRANSFORM)->rotation.y += 3.1415/4.0;
	Get<GameObject*>(sphereObj)->GetComponent<Transform*>(pType::TRANSFORM)->rotation.z += 3.1415 / 4.0;
	Get<GameObject*>(cubeObj)->GetComponent<Transform*>(pType::TRANSFORM)->location.x += 3.0;

	return true;
}

void ObjectFactory::Update(float dt) {
	for (int i = 0; i < gameObjects.size(); i++) {
		if (gameObjects[i] != nullptr) {
			gameObjects[i]->Update();
		}
	}
}

void* ObjectFactory::Get(Handle h) {
	return resourceManager.Get(h);
}

Handle ObjectFactory::Add(void* pointer, pType type) {
	return resourceManager.Add(pointer, type);
}

template<typename T>
Handle ObjectFactory::CreateGameObject(string tag) {
	T* object = new T();
	//Create the game object
	int i;
	for (i = 0; i < gameObjects.size(); i++) {
		if (gameObjects[i] == nullptr) {
			gameObjects[i] = object;
			break;
		}
	}
	//Get a handle for it
	Handle objectHandle = Add(object, pType::GAME_OBJECT);
	//Pass it's own handle and the object tag to the game object
	object->handle = objectHandle;
	object->tag = tag;
	//Give game object a transform (All game objects need one)
	GiveTransform(objectHandle);
	return objectHandle;
}

/*

ADD COMPONENTS

*/
bool ObjectFactory::GiveTransform(Handle objHandle, vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 rotation = vec3(0.0f, 0.0f, 0.0f), vec3 scale = vec3(1.0f, 1.0f, 1.0f)) {
	GameObject* obj = Get<GameObject*>(objHandle);
	if (obj != nullptr) {
		//Game object does not have a transform
		if (!obj->HasComponent(pType::TRANSFORM)) {
			Handle transformHandle = Engine::physicsSys.CreateTransform(position, rotation, scale);
			Get<Transform*>(transformHandle)->gameObject = objHandle;
			obj->components[pType::TRANSFORM] = transformHandle;
			return true;

		//GameObject already has a transform, modify it's values to match input
		} else {
			Transform* existingTransform = Get<Transform*>(obj->components[pType::TRANSFORM]);
			existingTransform->location = position;
			existingTransform->rotation = rotation;
			existingTransform->scale = scale;
			return true;
		}
	}
	//Game object was null
	cout << "\nCannot add a transform to an object that doesn't exist";
	return false;
}

bool ObjectFactory::GiveMeshRenderer(Handle objHandle, Handle meshHandle) {
	GameObject* obj = Get<GameObject*>(objHandle);
	if (obj != nullptr) {
		//Game object can't already have a mesh render
		if (!obj->HasComponent(pType::MESH_RENDER)) {
			//Game object must have a transform
			if (!obj->HasComponent(pType::TRANSFORM)) {
				cout << "\nTrying to add Mesh Render to object without transform. Giving object with tag " << obj->tag << " default transform...";
				//Give a default transform if it doesn't have one
				GiveTransform(objHandle);
			}
			Handle meshRenderHandle = Engine::renderSys.CreateMeshRender(meshHandle);
			Get<MeshRender*>(meshRenderHandle)->gameObject = objHandle;
			obj->components[pType::MESH_RENDER] = meshRenderHandle;
			return true;

		//Already has a mesh render
		} else {
			//Simply update the existing component's mesh
			obj->GetComponent<MeshRender*>(pType::MESH_RENDER)->mesh = meshHandle;
			return true;
		}
	}
	//Game object was null
	cout << "\nCannot add a mesh render to an object that doesn't exist";
	return false;
}


bool ObjectFactory::DeleteGameObject(Handle objHandle) {
	return false;
}

