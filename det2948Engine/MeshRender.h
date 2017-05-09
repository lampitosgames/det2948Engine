#pragma once
class Mesh;
#include <string>
#include "Component.h"
#include "pType.h"
#include "Handle.h"

class MeshRender : public Component {
public:
	//This is a Mesh Render
	pType type = pType::MESH_RENDER;

	Handle mesh;

	MeshRender() {};
	MeshRender(Handle meshHandle);

	bool Start();
	void Update(float dt);

	Mesh* GetMesh();
};