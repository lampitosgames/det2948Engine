#include "GameObject.h"
#include <iostream>

GameObject::GameObject() {
	this->tag = "default";
}

GameObject::~GameObject() {
}

Component * GameObject::GetComponent(compType id) {
	return nullptr;
}

void GameObject::Start() {
}

void GameObject::Update() {
	cout << "\nUpdating " << this->tag;
}

void GameObject::Render() {
	cout << "\nRendering" << this->tag;
}
