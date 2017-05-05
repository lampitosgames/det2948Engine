#pragma once
#include <vector>
#include "pType.h"
#include "Handle.h"
#include "System.h"
#include "MeshRender.h"
#include "Material.h"
#include "Texture.h"
#include "Mesh.h"
#include "Shader.h"

class Render : public System {
public:
	//Components
	vector<MeshRender> meshRenders;
	int mereCount = 0;
	vector<Material> materials;
	int matCount = 0;
	//Resources
	vector<Texture> textures;
	int texCount = 0;
	vector<Mesh> meshes;
	int meCount = 0;
	vector<Shader> shaders;
	int shCount = 0;

	Handle defaultMaterial;
	Handle curCamera;

	Render() {};

	bool Start();
	void Update(float dt);

	template<typename T> T Get(Handle h);

	Handle Add(int pointerIndex, pType type);

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