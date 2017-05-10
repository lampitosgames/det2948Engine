#pragma once
#include "Scene.h"

class MainScene : public Scene {
public:
	MainScene() {}
	bool Start();
	void Update(float dt);
};