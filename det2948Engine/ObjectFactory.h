#pragma once
#include <vector>
#include <string>
#include "System.h"
#include "pType.h"
#include "Handle.h"
#include "HandleManager.h"
#include "GameObject.h"
#include <glm\glm.hpp>

using namespace std;
using namespace glm;

class ObjectFactory : public System {
private:
	//Debug test objects
	Handle sphereMesh;
	Handle cubeMesh;
	Handle rotatingCube;
	Handle sphereObj;

public:
	HandleManager resourceManager;
	vector<GameObject*> gameObjects;
	int goCount = 0;

	ObjectFactory();
	~ObjectFactory();

	bool Start();
	void Update(float dt);

	template<typename T> Handle CreateGameObject(string tag);
	bool DeleteGameObject(Handle objHandle);

	template<typename T> T Get(Handle h);

	Handle Add(int pointerIndex, pType type);

	//Create and add a transform component to the object
	bool GiveTransform(Handle objHandle, vec3 position, vec3 rotation, vec3 scale);
	bool GiveMeshRenderer(Handle objHandle, Handle meshHandle);
	//bool GiveMaterial(Handle objHandle, Handle matHandle);
	bool GiveRigidBody(Handle objHandle, float mass);
};

template<typename T> T ObjectFactory::Get(Handle h) {
	int index = resourceManager.Get(h);
	if (index == -1) {
		cout << "\nInvalid index held in pointer";
		return nullptr;
	}
	switch (h.type) {
		case pType::GAME_OBJECT:
			return (T)gameObjects[index];
		case pType::MATERIAL:
			return (T)&Engine::renderSys.materials[index];
		case pType::MESH:
			return (T)&Engine::renderSys.meshes[index];
		case pType::MESH_RENDER:
			return (T)&Engine::renderSys.meshRenders[index];
		case pType::SHADER:
			return (T)&Engine::renderSys.shaders[index];
		case pType::TEXTURE:
			return (T)&Engine::renderSys.textures[index];
		case pType::TRANSFORM:
			return (T)&Engine::physicsSys.transforms[index];
		case pType::RIGID_BODY:
			return (T)&Engine::physicsSys.rigidBodies[index];
		default:
			cout << "\nInvalid handle type";
			return nullptr;
	}
}