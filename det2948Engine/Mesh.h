#pragma once
#include <iostream>
#include <FreeImage.h>

#include <GL\glew.h>	// The order
#include <GLFW\glfw3.h> // Of these matters

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

using namespace std;
using namespace glm;

struct Vertex {
	vec3 loc;
	vec2 uv;
	vec3 normal;
};

struct VertInd {
	unsigned int locInd;
	unsigned int uvInd;
	unsigned int normInd;
};

class Mesh {
private:
	GLuint VBO;
	GLuint VAO;
	unsigned int vertCount = 0;

public:
	Mesh();
	bool bufferModel(string filepath);
	void Render();
};