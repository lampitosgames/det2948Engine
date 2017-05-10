#include "Engine.h"
#include "Handle.h"
#include "MainScene.h"
#include <map>
#include <iostream>
#include <GL\glew.h>	// The order
#include <GLFW\glfw3.h> // Of these matters
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

Timer Engine::time = Timer();
Window Engine::windowSys = Window();
Render Engine::renderSys = Render();
Physics Engine::physicsSys = Physics();
ObjectFactory Engine::OF = ObjectFactory();

MainScene Engine::activeScene = MainScene();

bool Engine::Start() {
	if (!Engine::windowSys.Start()) {
		cout << "\nWindow system failed to start";
		return false;
	}

	if (!Input::Start()) {
		cout << "\nInput system failed to start";
		return false;
	}

	if (!Engine::OF.Start()) {
		cout << "\Object Factory failled to start";
		return false;
	}

	if (!Engine::renderSys.Start()) {
		cout << "\nRender system failled to start";
		return false;
	}

	if (!Engine::physicsSys.Start()) {
		cout << "\nPhysics system failed to start";
		return false;
	}

	if (!Engine::activeScene.Start()) {
		cout << "\nScene failed to start";
		return false;
	}

	return true;
}

void Engine::Update(float dt) {
	//Update systems
	Engine::windowSys.Update(dt);
	Input::Update(dt);
	Engine::renderSys.Update(dt);
	Engine::physicsSys.Update(dt);
	Engine::OF.Update(dt);

	Engine::activeScene.Update(dt);

	if (Input::KeyUp(GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(Engine::windowSys.window, GLFW_TRUE);
	}
}

void Engine::GameLoop() {
	while (!glfwWindowShouldClose(Engine::windowSys.window)) {
		time.Update();
		Engine::Update(time.dt);
		//Copy back buffer to front.  Everything was rendered on the back buffer so now we display it
		glfwSwapBuffers(Engine::windowSys.window);
	}
}

