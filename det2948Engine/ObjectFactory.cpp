#include "ObjectFactory.h"
#include "Engine.h"
#include "Component.h"

bool ObjectFactory::Start() {
	return true;
}

void ObjectFactory::Update(float dt) {
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i].Update();
	}
}

//template<typename T>
//T ObjectFactory::Get(Handle h) {
//	switch (h.type) {
//	case compType::GAME_OBJECT:
//		GameObject* returnObj;
//		if (objectManager.Get<GameObject*>(h, returnObj)) {
//			return returnObj;
//		}
//		break;
//	case compType::TRANSFORM:
//		break;
//	}
//	return nullptr;
//}

void* ObjectFactory::Get(Handle h) {
	return objectManager.Get(h);
}

Handle ObjectFactory::CreateGameObject(objTypes type, string tag) {
	//Create the game object
	switch (type) {
	case GAME_OBJECT_OBJ:
		gameObjects.push_back(GameObject());
		break;
	case CAMERA_OBJ:
		gameObjects.push_back(Camera());
		break;
	default:
		return Handle();
	}
	//Get a handle for it
	Handle objectHandle = objectManager.Add(&(gameObjects[gameObjects.size() - 1]), compType::GAME_OBJECT);
	//Pass it's own handle and the object tag to the game object
	GameObject* objectPtr;
	objectPtr = (GameObject*)Get(objectHandle);
	(*objectPtr).handle = objectHandle;
	(*objectPtr).tag = tag;
	return objectHandle;
}



bool ObjectFactory::DeleteGameObject(Handle objHandle) {
	return false;
}

