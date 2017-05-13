#include "Window.h"

Window::Window() {
}

bool Window::Start() {
	if (glfwInit() == GL_FALSE) {
		return false;
	}
	//Set screen width and height
	this->screenWidth = 1920;
	this->screenHeight = 1080;
	//Create a windowed mode window
	//Creates a window with the parameters given.  Returns the address of the GLFWwindow struct.  Returns a nullptr if it fails to create the window
	this->window = glfwCreateWindow(screenWidth, screenHeight, "Daniel Timko DSA1 Engine", NULL, NULL);
	//Make the new window the currently active context, or quit
	if (this->window != nullptr) {
		glfwMakeContextCurrent(window);
	}
	else {
		glfwTerminate();
		return false;
	}
	//Initialize GLEW or quit
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		return false;
	}
	return true;
}

void Window::Update(float dt) {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


}

Window::~Window() {
	glfwTerminate();
}
