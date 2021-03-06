#pragma once
#include "Collider.h"

class AABBCollider : public Collider {
public:
	vec3 corner1;
	vec3 corner2;
	float xSize, ySize, zSize;
	float halfX, halfY, halfZ;

	AABBCollider(vec3 center, float xSizeIn = 2.0f, float ySizeIn = 2.0f, float zSizeIn = 2.0f);

	bool Start();
	void Update(float dt);
};