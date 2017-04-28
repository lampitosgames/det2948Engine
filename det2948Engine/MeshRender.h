#pragma once
#include <string>
#include "Component.h"
#include "pType.h"
#include "Handle.h"
#include "Mesh.h"

class MeshRender : public Component {
public:
	//This is a Mesh Render
	pType type = pType::MESH_RENDER;

	Handle mesh;

	MeshRender(Handle meshHandle);

	bool Start();
	void Update();

	Mesh* GetMesh();
};