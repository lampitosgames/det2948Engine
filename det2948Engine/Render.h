#pragma once
#include "pType.h"
#include "System.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "Texture.h"
#include "Material.h"
#include "HandleManager.h"
#include <vector>

class Render : public System {
public:
	//Components
	vector<Component> meshRenderers;
	vector<Material> materials;
	vector<Component> transforms;
	//Resources
	vector<Texture> textures;
	vector<Mesh> meshes;
	vector<Shader> shaders;

	Handle defaultMaterial;
	Handle testMesh;

	Handle curCamera;

	Render();

	bool Start();
	void Update(float dt);

	void* Get(Handle h);
	template<typename T> T Get(Handle h);

	Handle Add(void* pointer, pType type);

	/*
	
	COMPONENTS
	
	*/
	Handle CreateMaterial(Handle mTexture, Handle mShader);

	/*
	
	RESOURCES

	*/
	Handle CreateTexture(char* filepath);
	Handle CreateShader(char* vShaderPath, char* fShaderPath);
	Handle CreateMesh(string filepath);

	~Render();
};

template<typename T>
inline T Render::Get(Handle h) {
	return Engine::OF.Get<T>(h);
}