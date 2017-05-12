#pragma once
class Texture;
class Shader;
#include "Component.h"
#include "pType.h"
#include "Handle.h"
#include <glm\glm.hpp>

using namespace glm;

enum matType {
	COLOR_MAT,
	TEXTURE_MAT
};

class Material : public Component {
public:
	//This is a material
	pType type = pType::MATERIAL;
	matType matType = matType::COLOR_MAT;
	//Materials can be assigned to multiple gameObjects.  They should never contain a reference to their parent
	Handle gameObject = Handle();
	//For now, materials are just a texture and a shader wrapper
	Handle texture;
	//OR
	vec3 color;
	Handle shader;

	//Lighting Variables
	float specularMultiplier = 16.0f;
	float ambientIntensity = 0.2f;

	Material();
	Material(Handle texHandle, Handle shaderHandle);
	Material(Handle shaderHandle, vec3 color = vec3(1.0f, 1.0f, 1.0f));

	bool Start();
	void Update(float dt);

	Texture* GetTexture();
	Shader* GetShader();
	vec3 GetColor();

	void SetSpecular(float spec);
	void SetAmbient(float ambient);
};