#pragma once
class Texture;
class Shader;
#include "Component.h"
#include "pType.h"
#include "Handle.h"

class Material : public Component {
public:
	//This is a material
	pType type = pType::MATERIAL;
	//Materials can be assigned to multiple gameObjects.  They should never contain a reference to their parent
	Handle gameObject = Handle();
	//For now, materials are just a texture and a shader wrapper
	Handle texture;
	Handle shader;

	Material();
	Material(Handle texHandle, Handle shaderHandle);

	bool Start();
	void Update(float dt);

	Texture* GetTexture();
	Shader* GetShader();
};