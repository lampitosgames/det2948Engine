#include "Render.h"
#include "Engine.h"
#include <glm\glm.hpp>
#include <iostream>

Render::Render() {
}

bool Render::Start() {
	defaultShader = CreateShader("shaders/vPhong.glsl", "shaders/fPhong.glsl");
	defaultTexture = CreateTexture("images/newTexture.png");
	testMesh = CreateMesh("models/sphere.obj");

	tempTex.Load();

	camera = Camera();

	glEnable(GL_DEPTH_TEST);
	return true;
}

void Render::Update(float dt) {
	Shader* curShader = (Shader*)Get(defaultShader);
	Texture* curTexture = (Texture*)Get(defaultTexture);
	Mesh* curMesh = (Mesh*)Get(testMesh);

	(*curShader).use();

	camera.Update();
	(*curShader).applyMatrix(&camera.camMatrix, glm::vec3(1.2f, 1.0f, 2.0f), camera.loc);

	(*curTexture).use();

	//Render
	(*curMesh).Render();
}

Handle Render::CreateTexture(char * filepath) {
	Texture newTexture = Texture(filepath);
	if (!newTexture.Load()) {
		cout << "\nTexture failed to load";
		return Handle();
	}
	textures.push_back(newTexture);
	return resourceManager.Add(&textures[textures.size() - 1], compType::TEXTURE);
}

Handle Render::CreateShader(char * vShaderPath, char * fShaderPath) {
	Shader newShader = Shader(vShaderPath, fShaderPath);
	if (newShader.load()) {
		//TODO: Delete this and add lighting support
		newShader.lightLoc = glm::vec3(1.2f, 1.0f, 2.0f);
	} else {
		cout << "\nShader failed to load\n";
		return Handle();
	}

	shaders.push_back(newShader);
	return resourceManager.Add(&shaders[shaders.size() - 1], compType::SHADER);
}

Handle Render::CreateMesh(string filepath) {
	Mesh newMesh = Mesh();
	if (!newMesh.bufferModel(filepath)) {
		cout << "\nFailed to load model";
		return Handle();
	}

	meshes.push_back(newMesh);
	return resourceManager.Add(&meshes[meshes.size() - 1], compType::MESH);
}

Render::~Render() {
	(*(Shader*)Get(defaultShader)).unload();
}
