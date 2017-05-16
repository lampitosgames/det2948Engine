#pragma once
#include <vector>
#include "Timer.h"
#include "Window.h"
#include "Input.h"
#include "Render.h"
#include "Physics.h"
#include "ObjectFactory.h"
#include "MainScene.h"

class Engine {
public:
	static Timer time;

	static Window windowSys;
	static Render renderSys;
	static Physics physicsSys;
	static ObjectFactory OF;

	static MainScene activeScene;

	static bool Start();

	static void GameLoop();
	static void Update(float dt);
};