#include "AABBCollider.h"

AABBCollider::AABBCollider(vec3 center, float xSizeIn, float ySizeIn, float zSizeIn) {
	this->type = colType::AABB_COL;
	xSize = xSizeIn;
	ySize = ySizeIn;
	zSize = zSizeIn;
	halfX = xSize * 0.5f;
	halfY = ySize * 0.5f;
	halfZ = zSize * 0.5f;
	corner1 = vec3(center.x - halfX, center.y - halfY, center.z - halfZ);
	corner2 = vec3(center.x + halfX, center.y + halfY, center.z + halfZ);
}

bool AABBCollider::Start() {
	return true;
}

void AABBCollider::Update(float dt) {
	vec3 center = GetTransform()->location;
	corner1 = vec3(center.x - halfX, center.y - halfY, center.z - halfZ);
	corner2 = vec3(center.x + halfX, center.y + halfY, center.z + halfZ);
}
