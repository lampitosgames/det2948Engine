#pragma once
class Transform;
#include <string>
#include "Component.h"
#include "pType.h"
#include "Handle.h"
#include <glm\glm.hpp>

using namespace glm;

class RigidBody : public Component {
public:
	//This is a Mesh Render
	pType type = pType::RIGID_BODY;

	//Physical variables
	vec3 netForce = vec3(0.0f, 0.0f, 0.0f);
	vec3 vel;
	vec3 accel;
	float mass;
	float cDrag = 0.5f; //Coeffecient of drag
	float restitution = -0.5f;
	float surfaceArea = 0.01f;

	//Do global forces get applied to this object?
	bool hasGravity = false;
	bool hasDrag = false;
	
	RigidBody(float mass = 1.0f, vec3 vel = vec3(0.0f, 0.0f, 0.0f));

	bool Start();
	void Update(float dt);

	//Apply forces
	void ApplyForce(vec3 force);
	void ApplyGravity(vec3 grav);
	void ApplyDrag(float density);

	Transform* GetTransform();
	
	/*bool hasCollider = false;
	Handle collider;
	Collider* GetCollider();*/
};
