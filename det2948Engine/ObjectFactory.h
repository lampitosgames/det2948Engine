#pragma once
#include <vector>
#include "pType.h"
#include "GameObject.h"
#include "HandleManager.h"
#include "Handle.h"
#include "System.h"
#include <glm\glm.hpp>

using namespace std;
using namespace glm;

class ObjectFactory : public System {
private:
	HandleManager resourceManager;

	//Debug test objects
	Handle sphereMesh;
	Handle cubeMesh;
	Handle rotatingCube;
	Handle sphereObj;

public:
	GameObject* gameObjects[typeArraySize];
	int goCount = 0;

	ObjectFactory();
	~ObjectFactory();

	bool Start();
	void Update(float dt);

	template<typename T> Handle CreateGameObject(string tag);
	bool DeleteGameObject(Handle objHandle);

	void* Get(Handle h);
	template<typename T> T Get(Handle h);

	Handle Add(void* pointer, pType type);

	//Create and add a transform component to the object
	bool GiveTransform(Handle objHandle, vec3 position, vec3 rotation, vec3 scale);
	bool GiveMeshRenderer(Handle objHandle, Handle meshHandle);
	//bool GiveMaterial(Handle objHandle, Handle matHandle);
};

template<typename T>
inline T ObjectFactory::Get(Handle h) {
	T returnPointer;
	if (resourceManager.Get<T>(h, returnPointer)) {
		return returnPointer;
	}
	cout << "\nInvalid handle, pointer not found";
	return nullptr;
}