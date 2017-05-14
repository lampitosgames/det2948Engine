#pragma once
#include "Component.h"
#include "Transform.h"
#include "RigidBody.h"

enum colType {
	SPHERE_COL = 0,
	AABB_COL = 1,
	OBB_COL = 2,
	MESH_COL = 3
};
class Collider : public Component {
public:
	colType type;
	virtual bool Start();
	virtual void Update(float dt);

	Transform* GetTransform();
	RigidBody* GetRigidBody();
	vec3 pos();
	vec3 vel();
	vec3 scale();
};