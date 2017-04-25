#pragma once
#include <string>
#include <FreeImage.h>

#include <GL\glew.h>	// The order
#include <GLFW\glfw3.h> // Of these matters

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

using namespace std;

class Texture {
public:
	char* filepath = "images/testTexture.png";
	GLuint texID;

	Texture();
	~Texture();
	bool Load();
	void use();
};