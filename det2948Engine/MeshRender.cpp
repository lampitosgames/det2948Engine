#include "MeshRender.h"
#include "Engine.h"

MeshRender::MeshRender(Handle meshHandle) {
	this->mesh = meshHandle;
}

bool MeshRender::Start() {
	return true;
}

void MeshRender::Update(float dt) {
}

Mesh * MeshRender::GetMesh() {
	return Engine::OF.Get<Mesh*>(this->mesh);
}
