#include "Shader.h"
#include <iostream>
#include <fstream>
#include <GL\glew.h>	// The order
#include <GLFW\glfw3.h> // Of these matters
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

Shader::Shader() {
	this->filenamev = "shaders/vPhong.glsl";
	this->filenamef = "shaders/fPhong.glsl";
}

Shader::Shader(string vFilepath, string fFilepath) {
	this->filenamev = vFilepath;
	this->filenamef = fFilepath;
}

bool Shader::load() {
	//Compile both shaders and only continue if they compile successfully
	if (compile(GL_VERTEX_SHADER) && compile(GL_FRAGMENT_SHADER)) {
		//Create a program and upload both shaders
		this->program = glCreateProgram();
		glAttachShader(this->program, this->vprogram);
		glAttachShader(this->program, this->fprogram);
		glLinkProgram(this->program);

		//Check for successful compile
		GLint linkSuccess;
		glGetProgramiv(this->program, GL_LINK_STATUS, &linkSuccess);
		//If the program succeeded, return true
		if (linkSuccess == GL_TRUE) {
			return true;
		}
		//Program failed.  Get log and print
		GLint logLength = 0;
		//If the log exists
		glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength > 1) {
			//Get the log
			GLchar* compilerLog = (GLchar*)malloc(logLength);
			glGetProgramInfoLog(this->program, logLength, NULL, compilerLog);
			//Print the log
			std::cout << "\ncompilerLog:\n" << compilerLog;
			delete[] compilerLog;
		}
		//Cleanup and return false
		glDeleteShader(this->vprogram);
		glDeleteShader(this->fprogram);
		glDeleteProgram(this->program);
	}
	return false;
}

bool Shader::compile(GLenum shaderType) {
	//Initialize variables
	ifstream instream;
	GLuint newShader;

	if (shaderType == GL_VERTEX_SHADER) {
		//Open the shader
		instream = ifstream(this->filenamev, std::ios::binary);
		if (!instream.is_open()) { return false; }
		newShader = glCreateShader(GL_VERTEX_SHADER);

	} else if (shaderType == GL_FRAGMENT_SHADER) {
		//Open the shader
		instream = ifstream(this->filenamef, std::ios::binary);
		if (!instream.is_open()) { return false; }
		newShader = glCreateShader(GL_FRAGMENT_SHADER);
	}

	//Get length
	instream.seekg(0, std::ios::end); //go to the end of the file.  once we skim the whole file, we can figure out how large it is.
	int length = (int)instream.tellg(); //how long is the file?
	instream.seekg(0, std::ios::beg); //go back to the beginning of the file so we can read the contents

	//Read the entire file into a char aray
	GLchar* shaderSrc = new char[length + 1];
	shaderSrc[length] = '\0';
	instream.read(shaderSrc, length);

	//Pass the source code to the new shader & compile
	glShaderSource(newShader, 1, &shaderSrc, NULL);
	glCompileShader(newShader);

	//Check for successful compile
	GLint compileSuccess;
	glGetShaderiv(newShader, GL_COMPILE_STATUS, &compileSuccess);
	//If compile failed
	if (compileSuccess == GL_FALSE) {
		//Initialize logging variables
		GLint logLength = 0;

		//If the log exists
		glGetShaderiv(newShader, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength > 1) {
			//Get the log
			GLchar* compilerLog = (GLchar*)malloc(logLength);
			glGetShaderInfoLog(newShader, logLength, NULL, compilerLog);
			//Print the log
			std::cout << "\ncompilerLog:\n" << compilerLog;
			delete[] compilerLog;
		}
		//Cleanup and return false
		glDeleteShader(newShader);
		delete[] shaderSrc;
		return false;

	//Compile was a success
	} else {
		//Set the class programs
		if (shaderType == GL_VERTEX_SHADER) {
			this->vprogram = newShader;
		} else if (shaderType == GL_FRAGMENT_SHADER) {
			this->fprogram = newShader;
		}
		//Clean up and return true
		delete[] shaderSrc;
		return true;
	}
}

void Shader::applyCameraMatrix(glm::mat4 * cameraMatrix) {
	//Upload camera matrix
	GLint camMatrix = glGetUniformLocation(this->program, "camMatrix");
	glUniformMatrix4fv(camMatrix, 1, GL_FALSE, glm::value_ptr(*cameraMatrix));
}

void Shader::applyLightInfo(glm::vec3 lightLocation, glm::vec3 camLocation, float specularMultiplier, float ambientIntensity) {
	//Upload light location
	GLint lightPos = glGetUniformLocation(this->program, "lightPos");
	glUniform3f(lightPos, lightLocation.x, lightLocation.y, lightLocation.z);

	//Upload cam location
	GLint camPos = glGetUniformLocation(this->program, "camPos");
	glUniform3f(camPos, camLocation.x, camLocation.y, camLocation.z);

	//Upload specular multiplier
	GLint specMultPos = glGetUniformLocation(this->program, "specularMultiplier");
	glUniform1f(specMultPos, specularMultiplier);
	//Upload ambient intensity
	GLint ambIntPos = glGetUniformLocation(this->program, "ambientIntensity");
	glUniform1f(ambIntPos, ambientIntensity);
}

void Shader::applyModelMatrix(glm::mat4 * modelMatrix) {
	//Upload camera matrix
	GLint camMatrix = glGetUniformLocation(this->program, "modelMatrix");
	glUniformMatrix4fv(camMatrix, 1, GL_FALSE, glm::value_ptr(*modelMatrix));
}

void Shader::applyColor(vec3 color) {
	GLint colorLoc = glGetUniformLocation(this->program, "matColor");
	glUniform3f(colorLoc, color.x, color.y, color.z);
}

void Shader::use() {
	glUseProgram(this->program);
}

void Shader::unload() {
	glDeleteShader(this->vprogram);
	glDeleteShader(this->fprogram);
	glDeleteProgram(this->program);
}
