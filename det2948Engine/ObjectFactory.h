#pragma once
#include <vector>
#include "HandleManager.h"
#include "Handle.h"
#include "System.h"
#include "GameObject.h"
#include "Message.h"

using namespace std;

class ObjectFactory : public System {
private:
	enum objTypes {gameObject = 0};
	HandleManager objectManager;

	Handle testObj1;
	Handle testObj2;

public:
	vector<GameObject> gameObjects;

	bool Start();
	void Update(float dt);

	Handle CreateGameObject(string tag);
	//Add a default component to an object.  Returns false if it fails, or if the object already has a component of that type
	bool AddComponent(Handle objHandle, compType type);

	bool DeleteGameObject(Handle objHandle);
};