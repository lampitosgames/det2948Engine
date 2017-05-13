#pragma once
#include "Collider.h"

class SphereCollider : public Collider {
public:
	float radius;

	SphereCollider(float radius);

	bool Start();
	void Update(float dt);

	float maxScale();
};