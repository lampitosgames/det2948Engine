#pragma once
#include <string>
#include <iostream>
#include "Handle.h"
#include "pType.h"
#include "Handle.h"
#include "HandledObject.h"
#include "Engine.h"

using namespace std;

class GameObject : public HandledObject {
public:
	Handle components[numpTypes];
	string tag;

	GameObject();
	virtual ~GameObject();

	template<typename T> T GetComponent(pType type);
	bool HasComponent(pType type);

	virtual void Start();
	virtual void Update();
};

template<typename T>
inline T GameObject::GetComponent(pType type) {
	return Engine::OF.Get<T>(components[type]);
}
