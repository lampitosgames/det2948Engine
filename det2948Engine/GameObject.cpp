#include "GameObject.h"
#include <iostream>

GameObject::GameObject() {
	this->tag = "default";
}

GameObject::~GameObject() {
}

Handle GameObject::GetComponent(compType id) {
	return Handle();
}

void GameObject::Start() {
}

void GameObject::Update() {
	//cout << "\nUpdating " << this->tag;
}
