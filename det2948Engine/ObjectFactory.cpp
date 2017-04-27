#include "ObjectFactory.h"
#include "Engine.h"
#include "Component.h"

ObjectFactory::ObjectFactory() {
}

ObjectFactory::~ObjectFactory() {
	for (int i = 0; i < gameObjects.size(); i++) {
		delete gameObjects[i];
	}
}

bool ObjectFactory::Start() {
	testObj1 = CreateGameObject<GameObject>("object1");
	Engine::renderSys.curCamera = Engine::OF.CreateGameObject<Camera>("MainCamera");
	return true;
}

void ObjectFactory::Update(float dt) {
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->Update();
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
	gameObjects.push_back(object);
	//Get a handle for it
	Handle objectHandle = Add(object, pType::GAME_OBJECT);
	//Pass it's own handle and the object tag to the game object
	object->handle = objectHandle;
	object->tag = tag;
	return objectHandle;
}



bool ObjectFactory::DeleteGameObject(Handle objHandle) {
	return false;
}

