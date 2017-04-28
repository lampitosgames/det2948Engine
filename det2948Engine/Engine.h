#pragma once
#include "System.h"
#include "Render.h"
#include "Window.h"
#include "Physics.h"
#include "ObjectFactory.h"

#include <vector>
#include "System.h"
#include "Timer.h"

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