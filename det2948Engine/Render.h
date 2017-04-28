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
	vector<MeshRender> meshRenders;
	vector<Material> materials;
	//Resources
	vector<Texture> textures;
	vector<Mesh> meshes;
	vector<Shader> shaders;

	Handle defaultMaterial;
	Handle testMesh;

	Handle curCamera;

	Render() : meshRenders(100), materials(100), textures(100), meshes(100), shaders(100) {};

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