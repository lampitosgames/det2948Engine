#include "Render.h"
#include <glm\glm.hpp>
#include <iostream>

Render::Render() {
}

bool Render::Start() {
	//load shaders
	if (phongShader.load()) {
		phongShader.lightLoc = glm::vec3(1.2f, 1.0f, 2.0f);
		cout << "\nshader loaded successfully\n";
	} else {
		cout << "\nshader failed to load\n";
		return false;
	}

	if (!teapotMesh.bufferModel("models/sphere.obj")) {
		cout << "\nError loading model";
		return false;
	}

	if (!texture.Load()) {
		return false;
	}

	glEnable(GL_DEPTH_TEST);
	return true;
}

void Render::Update(float dt) {
	phongShader.use();

	camera.Update();
	phongShader.applyMatrix(&camera.camMatrix, glm::vec3(1.2f, 1.0f, 2.0f), camera.loc);

	texture.use();

	//Render
	teapotMesh.Render();
}

Render::~Render() {
	phongShader.unload();
}
