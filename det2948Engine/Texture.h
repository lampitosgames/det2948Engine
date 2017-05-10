#pragma once
#include "HandledObject.h"
#include <GL\glew.h>	// The order
#include <GLFW\glfw3.h> // Of these matters

using namespace std;

class Texture : public HandledObject {
public:
	char* filepath;
	GLuint texID;

	Texture();
	Texture(char* inFilepath);
	~Texture();
	bool Load();
	void Unload();
	void use();
};