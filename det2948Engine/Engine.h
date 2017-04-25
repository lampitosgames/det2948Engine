#pragma once
#include "System.h"
#include "Render.h"
#include "Window.h"
#include "ObjectFactory.h"

#include <vector>
#include "System.h"
#include "Timer.h"

using namespace std;

static class Engine {
public:
	static Timer time;

	static Window windowSys;
	static Render renderSys;
	static ObjectFactory objFactorySys;

	static bool Start();

	static void GameLoop();
	static void Update(float dt);

	//TEMP
	static void HandleCameraInput();
};