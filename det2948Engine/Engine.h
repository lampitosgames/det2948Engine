#pragma once
#include <vector>
#include "Timer.h"
#include "Window.h"
#include "Render.h"
#include "Physics.h"
#include "ObjectFactory.h"

static class Engine {
public:
	static Timer time;

	static Window windowSys;
	static Render renderSys;
	static Physics physicsSys;
	static ObjectFactory OF;

	static bool Start();

	static void GameLoop();
	static void Update(float dt);

	//TEMP
	static void HandleCameraInput();
};