#pragma once
#include <string>
#include <iostream>
#include "Component.h"
#include "Handle.h"
#include "HandledObject.h"

using namespace std;

class GameObject : public HandledObject {
private:
	Handle components[numCompTypes];
public:
	string tag;

	GameObject();
	virtual ~GameObject();

	Component* GetComponent(compType);
	void AddComponent(Component* comp);
	bool HasComponent(compType);

	virtual void Start();
	virtual void Update();
	void Render();
};