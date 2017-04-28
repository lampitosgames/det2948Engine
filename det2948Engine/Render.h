#pragma once
#include "pType.h"
#include "System.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "Texture.h"
#include "Material.h"
#include "MeshRender.h"
#include "HandleManager.h"
#include <vector>

class Render : public System {
public:
	//Components
	MeshRender meshRenders[typeArraySize];
	int mereCount = 0;
	Material materials[typeArraySize];
	int matCount = 0;
	//Resources
	Texture textures[typeArraySize];
	int texCount = 0;
	Mesh meshes[typeArraySize];
	int meCount = 0;
	Shader shaders[typeArraySize];
	int shCount = 0;

	Handle defaultMaterial;
	Handle testMesh;

	Handle curCamera;

	Render() {};

	bool Start();
	void Update(float dt);

	void* Get(Handle h);
	template<typename T> T Get(Handle h);

	Handle Add(void* pointer, pType type);

	/*
	
	COMPONENTS
	
	*/
	Handle CreateMaterial(Handle mTexture, Handle mShader);
	Handle CreateMeshRender(Handle meshHandle);

	/*
	
	RESOURCES

	*/
	Handle CreateTexture(char* filepath);
	Handle CreateShader(char* vShaderPath, char* fShaderPath);
	Handle CreateMesh(string filepath);

	~Render();
};