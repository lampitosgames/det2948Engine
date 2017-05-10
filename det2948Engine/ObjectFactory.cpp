#include "ObjectFactory.h"
#include "Camera.h"
#include "BouncingBallObj.h"
#include "Engine.h"
#include "GameObject.h"
#include "Transform.h"
#include "MeshRender.h"
#include "Material.h"
#include "RigidBody.h"

ObjectFactory::ObjectFactory() {
}

ObjectFactory::~ObjectFactory() {
	for (int i = 0; i < goCount; i++) {
		delete gameObjects[i];
	}
}

bool ObjectFactory::Start() {
	return true;
}

void ObjectFactory::Update(float dt) {
	for (int i = 0; i < goCount; i++) {
		gameObjects[i]->Update();
		//Temp code for updating objects.  Eventually stuff like this will go in scripting components.
		if (gameObjects[i]->tag == "sphere" && glfwGetKey(Engine::windowSys.window, GLFW_KEY_SPACE)) {
			//Get<GameObject*>(sphereObj)->GetComponent<RigidBody*>(pType::RIGID_BODY)->ApplyForce(vec3(0.0f, 1.0f, 0.0f));
		}
	}
}




Handle ObjectFactory::Add(int pointerIndex, pType type) {
	return resourceManager.Add(pointerIndex, type);
}

/*

ADD COMPONENTS

*/
bool ObjectFactory::GiveTransform(Handle objHandle, vec3 position, vec3 rotation, vec3 scale) {
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

bool ObjectFactory::GiveMaterial(Handle objHandle, Handle matHandle) {
	GameObject* obj = Get<GameObject*>(objHandle);
	if (obj != nullptr) {
			obj->components[pType::MATERIAL] = matHandle;
			return true;
	}
	//Game object was null
	cout << "\nCannot add a material to an object that doesn't exist";
	return false;
}

bool ObjectFactory::GiveRigidBody(Handle objHandle, float mass) {
	GameObject* obj = Get<GameObject*>(objHandle);
	if (obj != nullptr) {
		//Game object can't already have a mesh render
		if (!obj->HasComponent(pType::RIGID_BODY)) {
			//Game object must have a transform
			if (!obj->HasComponent(pType::TRANSFORM)) {
				cout << "\nTrying to add Rigid Body to object without transform. Giving object with tag " << obj->tag << " default transform...";
				//Give a default transform if it doesn't have one
				GiveTransform(objHandle);
			}
			Handle rigidBodyHandle = Engine::physicsSys.CreateRigidBody(mass);
			Get<RigidBody*>(rigidBodyHandle)->gameObject = objHandle;
			obj->components[pType::RIGID_BODY] = rigidBodyHandle;
			return true;

		//Already has a mesh render
		} else {
			//Simply update the existing component's mesh
			obj->GetComponent<RigidBody*>(pType::RIGID_BODY)->mass = mass;
			return true;
		}
	}
	//Game object was null
	cout << "\nCannot add a rigid body to an object that doesn't exist";
	return false;
}


bool ObjectFactory::DeleteGameObject(Handle objHandle) {
	return false;
}

