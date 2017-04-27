#pragma once
#include "pType.h"
#include "Handle.h"
#include "HandledObject.h"

class Component : public HandledObject {
public:
	pType type;
	Handle gameObject;

	virtual bool Start() = 0;
	virtual void Update() = 0;
};