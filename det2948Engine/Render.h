#pragma once
#include "System.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include "Texture.h"
#include "HandleManager.h"

class Render : public System {
private:
	HandleManager handleManager = HandleManager();
public:
	Shader phongShader = Shader("shaders/vPhong.glsl", "shaders/fPhong.glsl");
	Mesh teapotMesh = Mesh();
	Camera camera = Camera();
	Texture texture = Texture();

	Render();

	bool Start();
	void Update(float dt);

	//Component creators
	Handle NewTransformComp();
	Handle NewMeshRendererComp();

	~Render();
};