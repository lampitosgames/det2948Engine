#pragma once
#include "System.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "Texture.h"
#include "Material.h"
#include "HandleManager.h"
#include <vector>

class Render : public System {
private:
	HandleManager componentManager = HandleManager();
	HandleManager resourceManager = HandleManager();
public:
	//Components
	vector<Component> meshRenderers;
	vector<Component> materials;
	vector<Component> transforms;
	//Resources
	vector<Texture> textures;
	vector<Mesh> meshes;
	vector<Shader> shaders;

	Camera camera;
	Handle testMesh;
	Handle defaultTexture;
	Handle defaultShader;

	Texture tempTex = Texture("images/testTexture.png");

	Render();

	bool Start();
	void Update(float dt);

	//template<typename T>
	//T Get(Handle h);
	void* Get(Handle h) { return resourceManager.Get(h); }

	Handle CreateTexture(char* filepath);
	Handle CreateShader(char* vShaderPath, char* fShaderPath);
	Handle CreateMesh(string filepath);

	~Render();
};

//template<typename T>
//inline T Render::Get(Handle h) {
//	switch (h.type) {
//	case compType::MESH:
//		Mesh* returnMesh;
//		if (resourceManager.Get<Mesh*>(h, returnMesh)) {
//			return returnMesh;
//		}
//		cout << "\nInvalid handle, mesh not found";
//		break;
//	case compType::SHADER:
//		Shader* returnShader;
//		if (resourceManager.Get<Shader*>(h, returnShader)) {
//			return returnShader;
//		}
//		cout << "\nInvalid handle, shader not found";
//		break;
//	case compType::TEXTURE:
//		Texture* returnTexture;
//		if (resourceManager.Get<Texture*>(h, returnTexture)) {
//			return returnTexture;
//		}
//		cout << "\nInvalid handle, texture not found";
//		break;
//	}
//	return nullptr;
//}
