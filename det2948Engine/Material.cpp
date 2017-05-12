class Shader;
class Texture;
#include "Material.h"
#include "Engine.h"

Material::Material() {

}

Material::Material(Handle texHandle, Handle shaderHandle) {
	this->texture = texHandle;
	this->shader = shaderHandle;
	this->color = vec3();
	this->matType = matType::TEXTURE_MAT;
}

Material::Material(Handle shaderHandle, vec3 color) {
	this->shader = shaderHandle;
	this->texture = Handle();
	this->color = color;
	this->matType = matType::COLOR_MAT;
}

bool Material::Start() {
	return true;
}

void Material::Update(float dt) {
}

Texture* Material::GetTexture() {
	return Engine::OF.Get<Texture*>(this->texture);
}

Shader* Material::GetShader() {
	return Engine::OF.Get<Shader*>(this->shader);
}

vec3 Material::GetColor() {
	return this->color;
}

void Material::SetSpecular(float spec) {
	this->specularMultiplier = spec;
}

void Material::SetAmbient(float ambient) {
	this->ambientIntensity = ambient;
}
