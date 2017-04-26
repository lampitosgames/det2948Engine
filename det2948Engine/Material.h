#pragma once
#include "Component.h"
#include "Handle.h"

class Material : public Component {
public:
	//Materials can be assigned to multiple gameObjects.  They should never contain a reference to their parent
	Handle gameObject = Handle();
	//For now, materials are just a texture and a shader wrapper
	Handle texture;
	Handle shader;

	Material(Handle texHandle, Handle shaderHandle);
};