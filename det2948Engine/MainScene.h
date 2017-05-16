#pragma once
#include "Scene.h"

class MainScene : public Scene {
public:
	Handle rotatingPlatform, rotatingPlatform2;
	float theta = 0.0f;
	MainScene() {}
	bool Start();
	void Update(float dt);
};