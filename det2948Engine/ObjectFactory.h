#pragma once
#include <vector>
#include "HandleManager.h"
#include "Handle.h"
#include "System.h"
#include "GameObject.h"
#include "Message.h"
#include <glm\glm.hpp>

using namespace std;
enum objTypes { GAME_OBJECT_OBJ, CAMERA_OBJ };

class ObjectFactory : public System {
private:
	HandleManager objectManager;

	Handle testObj1;
	Handle testObj2;

public:
	vector<GameObject> gameObjects;

	bool Start();
	void Update(float dt);

	Handle CreateGameObject(objTypes type, string tag);
	bool DeleteGameObject(Handle objHandle);

	//template<typename T>
	//T Get(Handle h);
	void* Get(Handle h);

	//Create and add a transform component to the object
	//bool GiveTransform(Handle objHandle, vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 rotation = vec3(0.0f, 0.0f, 0.0f), vec3 scale = vec3(0.0f, 0.0f, 0.0f));
	//bool GiveMeshRenderer(Handle objHandle, Handle meshHandle);
	//bool GiveMaterial(Handle objHandle, Handle matHandle);
};