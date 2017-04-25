#pragma once
#include "Component.h"
#include <GL\glew.h>	// The order
#include <GLFW\glfw3.h> // Of these matters

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

using namespace glm;

class Transform : Component {
public:
	vec3 location;
	vec3 rotation;
	vec3 scale;
	//Combine to create a model-world transformation matrix
	//When uploaded to the shader, the code is now - gl_Position = worldView * modelWorld * vec4(location, 1);
	mat4 modelMatrix();
};