#include "RotatingPlatform.h"
#include "Transform.h"
#include "pType.h"
#include "Engine.h"
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

void RotatingPlatform::Start() {
	vec3 location = GetComponent<Transform*>(pType::TRANSFORM)->location;
	float distFromCenter = length(vec3(0.0f, location.y, 0.0f) - location);
}

void RotatingPlatform::Update() {
	//theta += 0.0872665f * Engine::time.dt;

	//GetComponent<Transform*>(pType::TRANSFORM)->location = vec3(/*cos(theta)**/distFromCenter, GetComponent<Transform*>(pType::TRANSFORM)->location.y, /*sin(theta)**/distFromCenter);
}
