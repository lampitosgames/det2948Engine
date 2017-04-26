#include "Material.h"

Material::Material(Handle texHandle, Handle shaderHandle) {
	this->texture = texHandle;
	this->shader = shaderHandle;
}
