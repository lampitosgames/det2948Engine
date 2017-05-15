#pragma once
#include "Collider.h"

class OBBCollider : public Collider {
public:
	float xSize, ySize, zSize;
	float halfX, halfY, halfZ;

	OBBCollider(float xSizeIn = 2.0f, float ySizeIn = 2.0f, float zSizeIn = 2.0f);

	bool Start();
	void Update(float dt);

	mat3 rot();
};