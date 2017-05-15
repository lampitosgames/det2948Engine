#include "OBBCollider.h"

OBBCollider::OBBCollider(float xSizeIn, float ySizeIn, float zSizeIn) {
	this->type = colType::OBB_COL;
	xSize = xSizeIn;
	ySize = ySizeIn;
	zSize = zSizeIn;
	halfX = xSize * 0.5f;
	halfY = ySize * 0.5f;
	halfZ = zSize * 0.5f;
}

bool OBBCollider::Start() {
	return true;
}

void OBBCollider::Update(float dt) {
}

mat3 OBBCollider::rot() {
	return GetTransform()->rotMatrix();
}
