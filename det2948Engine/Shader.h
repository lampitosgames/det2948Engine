#pragma once
#include "HandledObject.h"
#include <iostream>
#include <FreeImage.h>

#include <GL\glew.h>	// The order
#include <GLFW\glfw3.h> // Of these matters

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

using namespace std;

class Shader : public HandledObject {
private:
	GLuint program, vprogram, fprogram;
	string filenamev;
	string filenamef;
public:
	glm::vec3 lightLoc;

	Shader(string vFilepath, string fFilepath);

	//Load shaders.  Set the value of programs to 0 if it fails, or something other than 0 if it succeeds
	bool load();
	//Helper method used by load to read and compile a shader file and save the index where it is stored
	bool compile(GLenum shaderType);
	//Give the shader new matrices to use
	void applyMatrix(glm::mat4* cameraMatrix, glm::vec3 lightLocation, glm::vec3 camLocation);
	//calls glUseProgram(program).  a simple function wrapper
	void use();
	//Unloads and deallocates this shader's memory on the graphics card.
	void unload();
};
