#include "ObjectFactory.h"
#include "Engine.h"

bool ObjectFactory::Start() {
	testObj2 = CreateGameObject("testObject2");
	testObj1 = CreateGameObject("testObject1");
	return true;
}

void ObjectFactory::Update(float dt) {
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i].Update();
	}
}

Handle ObjectFactory::CreateGameObject(string tag) {
	//Create the game object
	gameObjects.push_back(GameObject());
	//Get a handle for it
	Handle objectHandle = objectManager.Add(&(gameObjects[gameObjects.size() - 1]), gameObject);
	//Pass it's own handle and the object tag to the game object
	GameObject* object;
	objectManager.Get(objectHandle, object);
	(*object).handle = objectHandle;
	(*object).tag = tag;
	return objectHandle;
}

bool ObjectFactory::AddComponent(Handle objHandle, compType type) {
	//Handle compHandle;
	////Get the game object we're adding to
	//GameObject* object;
	//if (!objectManager.Get(objHandle, object)) {
	//	return false;
	//}

	//switch (type) {
	//case Transform:
	//	compHandle = Engine::renderSys.NewTransformComp();
	//	break;
	//case MeshRenderer:
	//	compHandle = Engine::renderSys.NewMeshRendererComp();
	//	break;
	//case Material:
	//	break;
	//default:
	//	cout << "\nInvalid comp type when trying to add component to gameobject with tag: " << (*object).tag;
	//	return false;
	//}
	return false;
}

bool ObjectFactory::DeleteGameObject(Handle objHandle) {
	return false;
}
