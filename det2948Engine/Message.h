#pragma once
#include "Camera.h"

enum mType {
	START,
	UPDATE,
	SET_ACTIVE_CAMERA
};

struct Message {
	mType type;
};

struct mStart : Message {
	mType type = START;
};

struct mUpdate : Message {
	mType type = UPDATE;
};

struct mSetActiveCamera : Message {
	mType type = SET_ACTIVE_CAMERA;
	Camera activeCamera;
};