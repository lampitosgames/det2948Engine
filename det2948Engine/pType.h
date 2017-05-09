#pragma once

enum pType {
	//Components
	TRANSFORM = 0,
	MESH_RENDER = 1,
	MATERIAL = 2,
	RIGID_BODY = 3,
	//Game-Objects
	GAME_OBJECT = 4,
	//Resources
	MESH = 5,
	SHADER = 6,
	TEXTURE = 7
};

const int numpTypes = 4;
const int typeArraySize = 256;