#pragma once
#include "HandledObject.h"
#include <string>
#include <FreeImage.h>

#include <GL\glew.h>	// The order
#include <GLFW\glfw3.h> // Of these matters

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

using namespace std;

class Texture : public HandledObject {
public:
	char* filepath;
	GLuint texID;

	Texture(char* inFilepath);
	~Texture();
	bool Load();
	void use();
};