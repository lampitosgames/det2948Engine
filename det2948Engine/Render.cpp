#include "Render.h"
#include "pType.h"
#include "Camera.h"
#include "Engine.h"
#include <glm\glm.hpp>
#include <iostream>

Render::Render() {
}

bool Render::Start() {
	Handle defaultShader = CreateShader("shaders/vPhong.glsl", "shaders/fPhong.glsl");
	Handle defaultTexture = CreateTexture("images/debugTexture.png");
	defaultMaterial = CreateMaterial(defaultTexture, defaultShader);
	testMesh = CreateMesh("models/sphere.obj");

	glEnable(GL_DEPTH_TEST);
	return true;
}

void Render::Update(float dt) {
	Camera* camPtr = Get<Camera*>(curCamera);
	Material* curMat = Get<Material*>(defaultMaterial);
	Mesh* curMesh = Get<Mesh*>(testMesh);

	curMat->GetShader()->use();

	camPtr->Update();
	curMat->GetShader()->applyMatrix(&camPtr->camMatrix, glm::vec3(1.2f, 1.0f, 2.0f), camPtr->loc);

	curMat->GetTexture()->use();

	//Render
	curMesh->Render();
}

void* Render::Get(Handle h) {
	return Engine::OF.Get(h);
}

Handle Render::Add(void* pointer, pType type) {
	return Engine::OF.Add(pointer, type);
}

/*

COMPONENTS

*/
Handle Render::CreateMaterial(Handle mTexture, Handle mShader) {
	materials.push_back(Material(mTexture, mShader));
	Handle matHandle = Add(&materials[materials.size() - 1], pType::MATERIAL);
	materials[materials.size() - 1].handle = matHandle;
	return matHandle;
}

/*

CREATE RESOURCES

*/
Handle Render::CreateTexture(char * filepath) {
	textures.push_back(Texture(filepath));
	if (textures[textures.size()-1].Load()) {
		Handle texHandle = Add(&textures[textures.size() - 1], pType::TEXTURE);
		textures[textures.size() - 1].handle = texHandle;
		return texHandle;
	}
	cout << "\nTexture failed to load";
	textures.erase(textures.end() - 1);
	return Handle();
}

Handle Render::CreateShader(char * vShaderPath, char * fShaderPath) {
	shaders.push_back(Shader(vShaderPath, fShaderPath));
	if (shaders[shaders.size()-1].load()) {
		//TODO: Delete this and add lighting support
		shaders[shaders.size() - 1].lightLoc = glm::vec3(1.2f, 1.0f, 2.0f);
		Handle sdrHandle = Add(&shaders[shaders.size() - 1], pType::SHADER);
		shaders[shaders.size() - 1].handle = sdrHandle;
		return sdrHandle;
	}
	cout << "\nShader failed to load\n";
	shaders.erase(shaders.end() - 1);
	return Handle();
}

Handle Render::CreateMesh(string filepath) {
	meshes.push_back(Mesh());
	if (meshes[meshes.size()-1].bufferModel(filepath)) {
		Handle mesHandle = Add(&meshes[meshes.size() - 1], pType::MESH);
		meshes[meshes.size() - 1].handle = mesHandle;
		return mesHandle;
	}
	cout << "\nFailed to load model";
	return Handle();
}

Render::~Render() {
	Get<Material*>(defaultMaterial)->GetShader()->unload();
}
