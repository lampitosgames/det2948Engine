#pragma once
#include "GameObject.h"

using namespace glm;

class RotatingPlatform : public GameObject {
public:
	float theta = 0.0f;
	float distFromCenter = 0.0f;
	void Start();
	void Update();
};