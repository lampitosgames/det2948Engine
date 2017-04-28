#include "Render.h"
#include "pType.h"
#include "Camera.h"
#include "Engine.h"
#include <glm\glm.hpp>
#include <iostream>

bool Render::Start() {
	Handle defaultShader = CreateShader("shaders/vPhong.glsl", "shaders/fPhong.glsl");
	Handle defaultTexture = CreateTexture("images/debugTexture.png");
	defaultMaterial = CreateMaterial(defaultTexture, defaultShader);
	//START ALL MESH RENDERS
	for (int i = 0; i < meshRenders.size(); i++) {
		if (!meshRenders[i].Start()) {
			//delete the mesh render if it fails to start
		}
	}
	//START ALL MATERIALS
	for (int i = 0; i < materials.size(); i++) {
		if (!materials[i].Start()) {
			//delete the material if it fails to start
		}
	}

	glEnable(GL_DEPTH_TEST);
	return true;
}

void Render::Update(float dt) {
	//Get the current camera
	Camera* camPtr = Get<Camera*>(curCamera);
	if (camPtr == nullptr) {
		cout << "\nNO VALID CAMERA";
		return;
	}

	//Loop through all mesh renders
	for (int i = 0; i < meshRenders.size(); i++) {
		//Get the object's mesh
		Mesh* curMesh = meshRenders[i].GetMesh();
		if (curMesh == nullptr) { continue; }
		
		//Get the object's transform6
		GameObject* obj = meshRenders[i].GetGameObject();
		Transform* curTransform = obj->GetComponent<Transform*>(pType::TRANSFORM);
		if (curTransform == nullptr) { continue; }

		Engine::physicsSys.transforms;

		//Get the object's material (or the default)
		Material* curMat = nullptr;// meshRenders[i].GetGameObject()->GetComponent<Material*>(pType::MATERIAL);
		if (curMat == nullptr) {
			curMat = Get<Material*>(defaultMaterial);
		}

		curMat->GetShader()->use();

		camPtr->Update();
		curMat->GetShader()->applyCameraMatrix(&camPtr->camMatrix);
		curMat->GetShader()->applyModelMatrix(&curTransform->modelMatrix());
		curMat->GetShader()->applyLightInfo(glm::vec3(1.2f, 1.0f, 2.0f), camPtr->loc);

		curMat->GetTexture()->use();

		//Render
		curMesh->Render();
	}
}

void* Render::Get(Handle h) {
	return Engine::OF.Get(h);
}

Handle Render::Add(void* pointer, pType type) {
	return Engine::OF.Add(pointer, type);
}

template<typename T>
inline T Render::Get(Handle h) {
	return Engine::OF.Get<T>(h);
}

/*

COMPONENTS

*/
Handle Render::CreateMaterial(Handle mTexture, Handle mShader) {
	if (mTexture != Handle() && mShader != Handle()) {
		materials.push_back(Material(mTexture, mShader));
		Handle matHandle = Add(&materials[materials.size() - 1], pType::MATERIAL);
		materials[materials.size() - 1].handle = matHandle;
		return matHandle;
	}
	cout << "\nInvalid texture or shader handle pased to CreateMaterial";
	return Handle();
}

Handle Render::CreateMeshRender(Handle meshHandle) {
	//Check for valid mesh
	if (meshHandle == Handle()) {
		return Handle();
	}
	meshRenders.push_back(MeshRender(meshHandle));
	Handle meshRenderHandle = Add(&meshRenders[meshRenders.size() - 1], pType::MESH_RENDER);
	meshRenders[meshRenders.size() - 1].handle = meshRenderHandle;
	return meshRenderHandle;
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
