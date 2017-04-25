#pragma once
#include <iostream>
#include <string>
#include "Timer.h"
#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"
#include "Light.h"

#include <FreeImage.h>

#include <GL\glew.h>	// The order
#include <GLFW\glfw3.h> // Of these matters

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

using namespace std;

static class EngineO {
public:
	static GLFWwindow* windowPtr;
	static int screenWidth;
	static int screenHeight;
	static Timer timer;
	static Shader shader;
	static Camera camera;
	static Mesh mesh;
	static Light light;

	static bool Start();
	static void Stop();
	static void Update();
	static void HandleCameraInput();
};
