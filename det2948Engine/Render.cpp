#include "Render.h"
#include <glm\glm.hpp>
#include <iostream>
#include "Camera.h"
#include "Engine.h"

bool Render::Start() {
	Handle defaultShader = CreateShader("shaders/vPhongColor.glsl", "shaders/fPhongColor.glsl");
	defaultMaterial = CreateMaterial(defaultShader);

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
	for (int i = 0; i < mereCount; i++) {
		//Get the object's mesh
		Mesh* curMesh = meshRenders[i].GetMesh();
		if (curMesh == nullptr) { continue; }
		
		//Get the object's transform6
		GameObject* obj = meshRenders[i].GetGameObject();
		if (!obj->isActive) { continue; }
		Transform* curTransform = obj->GetComponent<Transform*>(pType::TRANSFORM);
		if (curTransform == nullptr) { continue; }

		//Get the object's material (or the default)
		Material* curMat = obj->GetComponent<Material*>(pType::MATERIAL);
		if (curMat == nullptr) {
			curMat = Get<Material*>(defaultMaterial);
		}

		curMat->GetShader()->use();

		curMat->GetShader()->applyCameraMatrix(&camPtr->camMatrix);
		curMat->GetShader()->applyModelMatrix(&curTransform->modelMatrix());
		curMat->GetShader()->applyLightInfo(glm::vec3(120.0f, 100.0f, 200.0f), camPtr->GetComponent<Transform*>(pType::TRANSFORM)->location, curMat->specularMultiplier, curMat->ambientIntensity);

		if (curMat->matType == matType::TEXTURE_MAT) {
			curMat->GetTexture()->use();
		} else if (curMat->matType == matType::COLOR_MAT) {
			curMat->GetShader()->applyColor(curMat->GetColor());
		}

		//Render
		curMesh->Render();
	}
}

Handle Render::Add(int pointerIndex, pType type) {
	return Engine::OF.Add(pointerIndex, type);
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
		matCount += 1;
		Handle matHandle = Add(matCount - 1, pType::MATERIAL);
		materials[matCount - 1].handle = matHandle;
		materials[matCount - 1].index = matCount - 1;
		if (!materials[matCount - 1].Start()) {
			cout << "\nMaterial failed to start";
			matCount -= 1;
			materials.erase(materials.begin() + matCount);

			return Handle();
		}
		return matHandle;
	}
	cout << "\nInvalid texture or shader handle pased to CreateMaterial";
	return Handle();
}

Handle Render::CreateMaterial(Handle mShader, vec3 color) {
	if (mShader != Handle()) {
		materials.push_back(Material(mShader, color));
		matCount += 1;
		Handle matHandle = Add(matCount - 1, pType::MATERIAL);
		materials[matCount - 1].handle = matHandle;
		materials[matCount - 1].index = matCount - 1;
		if (!materials[matCount - 1].Start()) {
			cout << "\nMaterial failed to start";
			matCount -= 1;
			materials.erase(materials.begin() + matCount);

			return Handle();
		}
		return matHandle;
	}
	cout << "\nInvalid shader handle pased to CreateMaterial";
	return Handle();
}

Handle Render::CreateMeshRender(Handle meshHandle) {
	//Check for valid mesh
	if (meshHandle == Handle()) {
		return Handle();
	}
	meshRenders.push_back(MeshRender(meshHandle));
	mereCount += 1;
	Handle meshRenderHandle = Add(mereCount - 1, pType::MESH_RENDER);
	meshRenders[mereCount - 1].handle = meshRenderHandle;
	meshRenders[mereCount - 1].index = mereCount - 1;
	if (!meshRenders[mereCount - 1].Start()) {
		cout << "\nMeshRender failed to start";
		mereCount -= 1;
		meshRenders.erase(meshRenders.begin() + mereCount);
		return Handle();
	}
	return meshRenderHandle;
}

/*

CREATE RESOURCES

*/
Handle Render::CreateTexture(char * filepath) {
	textures.push_back(Texture(filepath));
	texCount += 1;
	if (textures[texCount-1].Load()) {
		Handle texHandle = Add(texCount - 1, pType::TEXTURE);
		textures[texCount - 1].handle = texHandle;
		return texHandle;
	}
	cout << "\nTexture failed to load";
	texCount -= 1;
	return Handle();
}

Handle Render::CreateShader(char * vShaderPath, char * fShaderPath) {
	shaders.push_back(Shader(vShaderPath, fShaderPath));
	shCount += 1;
	if (shaders[shCount-1].load()) {
		//TODO: Delete this and add lighting support
		shaders[shCount - 1].lightLoc = glm::vec3(1.2f, 1.0f, 2.0f);
		Handle sdrHandle = Add(shCount - 1, pType::SHADER);
		shaders[shCount - 1].handle = sdrHandle;
		shaders[shCount - 1].index = shCount - 1;
		return sdrHandle;
	}
	cout << "\nShader failed to load\n";
	shCount -= 1;
	return Handle();
}

Handle Render::CreateMesh(string filepath) {
	meshes.push_back(Mesh());
	meCount += 1;
	if (meshes[meCount -1].bufferModel(filepath)) {
		Handle mesHandle = Add(meCount - 1, pType::MESH);
		meshes[meCount - 1].handle = mesHandle;
		meshes[meCount - 1].index = meCount - 1;
		return mesHandle;
	}
	cout << "\nFailed to load model";
	meCount -= 1;
	return Handle();
}

Render::~Render() {
	Get<Material*>(defaultMaterial)->GetShader()->unload();
	for (int i = 0; i < texCount; i++) {
		textures[i].Unload();
	}
}
