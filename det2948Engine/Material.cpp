#include "Material.h"
#include "Texture.h"
#include "Engine.h"

Material::Material() {

}

Material::Material(Handle texHandle, Handle shaderHandle) {
	this->texture = texHandle;
	this->shader = shaderHandle;
}

bool Material::Start() {
	return true;
}

void Material::Update() {
}

Texture* Material::GetTexture() {
	return Engine::OF.Get<Texture*>(this->texture);
}

Shader* Material::GetShader() {
	return Engine::OF.Get<Shader*>(this->shader);
}
