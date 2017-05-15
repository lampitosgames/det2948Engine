#include "ObjectFactory.h"
#include "Camera.h"
#include "BouncingObj.h"
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

bool ObjectFactory::GiveRigidBody(Handle objHandle, float mass, float restitution) {
	GameObject* obj = Get<GameObject*>(objHandle);
	if (obj != nullptr) {
		//Game object can't already have a rigid body
		if (!obj->HasComponent(pType::RIGID_BODY)) {
			//Game object must have a transform
			if (!obj->HasComponent(pType::TRANSFORM)) {
				cout << "\nTrying to add Rigid Body to object without transform. Giving object with tag " << obj->tag << " default transform...";
				//Give a default transform if it doesn't have one
				GiveTransform(objHandle);
			}
			Handle rigidBodyHandle = Engine::physicsSys.CreateRigidBody(mass, vec3(), restitution);
			Get<RigidBody*>(rigidBodyHandle)->gameObject = objHandle;
			obj->components[pType::RIGID_BODY] = rigidBodyHandle;
			return true;

		//Already has a rigid body
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

bool ObjectFactory::GiveSphereCollider(Handle objHandle, float radius) {
	GameObject* obj = Get<GameObject*>(objHandle);
	if (obj != nullptr) {
		//Game object can't already have a collider
		if (!obj->HasComponent(pType::COLLIDER)) {
			//Game object must have a rigid body
			if (!obj->HasComponent(pType::RIGID_BODY)) {
				cout << "\nTrying to add sphere collider to object without rigid body. Giving object with tag " << obj->tag << " default rigid body...";
				//Give a default rigidbody if it doesn't have one
				GiveRigidBody(objHandle, 1.0f);
			}
			Handle sphereColliderHandle = Engine::physicsSys.CreateSphereCollider(radius);
			Get<SphereCollider*>(sphereColliderHandle)->gameObject = objHandle;
			obj->components[pType::COLLIDER] = sphereColliderHandle;
			return true;

		//Already has collider
		} else {
			cout << "\nError trying to add sphere collider to " << obj->tag << ".  Cannot add more than 1 collider to an object";
			return false;
		}
	}
	//Game object was null
	cout << "\nCannot add a sphere collider to an object that doesn't exist";
	return false;
}

bool ObjectFactory::GiveAABBCollider(Handle objHandle, vec3 corner1, vec3 corner2) {
	//Wrapper function
	return GiveAABBCollider(objHandle, abs(corner1.x - corner2.x), abs(corner1.y - corner2.y), abs(corner1.z - corner2.z));
}

bool ObjectFactory::GiveAABBCollider(Handle objHandle, float xSize, float ySize, float zSize) {
	GameObject* obj = Get<GameObject*>(objHandle);
	if (obj != nullptr) {
		//Game object can't already have a collider
		if (!obj->HasComponent(pType::COLLIDER)) {
			//Game object must have a rigid body
			if (!obj->HasComponent(pType::RIGID_BODY)) {
				cout << "\nTrying to add AABB collider to object without rigid body. Giving object with tag " << obj->tag << " default rigid body...";
				//Give a default rigidbody if it doesn't have one
				GiveRigidBody(objHandle, 1.0f);
			}
			vec3 centerPos = obj->GetComponent<Transform*>(pType::TRANSFORM)->location;
			Handle aabbColliderHandle = Engine::physicsSys.CreateAABBCollider(centerPos, xSize, ySize, zSize);
			Get<AABBCollider*>(aabbColliderHandle)->gameObject = objHandle;
			obj->components[pType::COLLIDER] = aabbColliderHandle;
			return true;

		//Already has collider
		} else {
			cout << "\nError trying to add AABB collider to " << obj->tag << ".  Cannot add more than 1 collider to an object";
			return false;
		}
	}
	//Game object was null
	cout << "\nCannot add an AABB collider to an object that doesn't exist";
	return false;
}

bool ObjectFactory::GiveOBBCollider(Handle objHandle, float xSize, float ySize, float zSize) {
	GameObject* obj = Get<GameObject*>(objHandle);
	if (obj != nullptr) {
		//Game object can't already have a collider
		if (!obj->HasComponent(pType::COLLIDER)) {
			//Game object must have a rigid body
			if (!obj->HasComponent(pType::RIGID_BODY)) {
				cout << "\nTrying to add OBB collider to object without rigid body. Giving object with tag " << obj->tag << " default rigid body...";
				//Give a default rigidbody if it doesn't have one
				GiveRigidBody(objHandle, 1.0f);
			}
			Handle obbColliderHandle = Engine::physicsSys.CreateOBBCollider(xSize, ySize, zSize);
			Get<OBBCollider*>(obbColliderHandle)->gameObject = objHandle;
			obj->components[pType::COLLIDER] = obbColliderHandle;
			return true;

		//Already has collider
		} else {
			cout << "\nError trying to add OBB collider to " << obj->tag << ".  Cannot add more than 1 collider to an object";
			return false;
		}
	}
	//Game object was null
	cout << "\nCannot add an OBB collider to an object that doesn't exist";
	return false;
}


bool ObjectFactory::DeleteGameObject(Handle objHandle) {
	return false;
}

