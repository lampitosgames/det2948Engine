#pragma once

enum pType {
	//Components
	TRANSFORM = 0,
	MESH_RENDER = 1,
	MATERIAL = 2,
	RIGID_BODY = 3,
	COLLIDER = 4,
	//Game-Objects
	GAME_OBJECT = 5,
	//Resources
	MESH = 6,
	SHADER = 7,
	TEXTURE = 8
};

const int numpTypes = 5;
const int typeArraySize = 256;