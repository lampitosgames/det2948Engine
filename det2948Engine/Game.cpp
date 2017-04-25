#include <iostream>
#include <vector>
#include "Engine.h"
#include "Shader.h"

// When we include with angle brackets, its in installed library directories (we didn't write it.
// the problem is that our OpenGL stuff isn't installed by default.  So we have to tell it where to look
// Go to Project->project settings->include directories->edit-> add new by using '$(ProjectDir)include'
// go to the same thing to include the libraries '$(ProjectDir)lib'
// You also need to go to project settings->linker->input->additional dependencies and add all of the .lib files
// THE SLIDES HAVE ALL OF THIS IN MORE DETAIL
#include <FreeImage.h>

#include <GL\glew.h>	// The order
#include <GLFW\glfw3.h> // Of these matters

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

int main() {
	if (!Engine::Start()) {
		return -1;
	}

	//Game loop
	//Loop until the user closes the window
	Engine::GameLoop();

	return 0;
}