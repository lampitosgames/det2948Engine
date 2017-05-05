#include "GameObject.h"

GameObject::GameObject() {
	this->tag = "default";
	for (int i = 0; i < numpTypes; i++) {
		components[i] = Handle();
	}
}

GameObject::~GameObject() {
}

bool GameObject::HasComponent(pType type) {
	return components[type] != Handle();
}

void GameObject::Start() {
}

void GameObject::Update() {
}
