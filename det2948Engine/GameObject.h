#pragma once
#include <string>
#include "pType.h"
#include <iostream>
#include "Component.h"
#include "Handle.h"
#include "HandledObject.h"

using namespace std;

class GameObject : public HandledObject {
private:
	Handle components[numpTypes];
public:
	string tag;

	GameObject();
	virtual ~GameObject();

	Handle GetComponent(pType type);
	bool HasComponent(pType type);

	virtual void Start();
	virtual void Update();
};