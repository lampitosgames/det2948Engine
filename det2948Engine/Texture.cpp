#include "Texture.h"
#include <FreeImage.h>

#include <GL\glew.h>	// The order
#include <GLFW\glfw3.h> // Of these matters

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

Texture::Texture() {
	filepath = "images/debugTexture.png";
}

Texture::Texture(char* inFilepath) {
	filepath = inFilepath;
}

Texture::~Texture() {
	glDeleteTextures(1, &texID);
}

bool Texture::Load() {
	FIBITMAP* image = FreeImage_Load(FreeImage_GetFileType(filepath, 0), filepath);
	if (image == nullptr) {
		return false;
	}
	FIBITMAP* image32Bit = FreeImage_ConvertTo32Bits(image);
	FreeImage_Unload(image);

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, FreeImage_GetWidth(image32Bit), FreeImage_GetHeight(image32Bit), 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(image32Bit));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	FreeImage_Unload(image32Bit);
	glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}

void Texture::use() {
	glBindTexture(GL_TEXTURE_2D, texID);
}
