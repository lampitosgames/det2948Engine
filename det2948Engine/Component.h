#pragma once
#include "Handle.h"
#include "HandledObject.h"

enum compType {
	Transform = 0,
	MeshRenderer = 1,
	Material = 2
};
const int numCompTypes = 3;

class Component : public HandledObject {
public:
	compType type;
	Handle gameObjecthandle;

	virtual bool Start() = 0;
	virtual void Update() = 0;
};