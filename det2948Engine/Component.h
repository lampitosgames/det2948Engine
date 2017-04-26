#pragma once
#include "Handle.h"
#include "HandledObject.h"

enum compType {
	//Non-component
	GAME_OBJECT = 0,
	//Components
	TRANSFORM = 1,
	MESH_RENDERER = 2,
	MATERIAL = 3,
	//Resources
	MESH = 4,
	SHADER = 5,
	TEXTURE = 6
};
const int numCompTypes = 3;

class Component : public HandledObject {
public:
	compType type;
	Handle gameObjecthandle;

	virtual bool Start() = 0;
	virtual void Update() = 0;
};