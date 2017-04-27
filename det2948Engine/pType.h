#pragma once

enum pType {
	//Components
	TRANSFORM = 0,
	MESH_RENDERER = 1,
	MATERIAL = 2,
	//Game-Objects
	GAME_OBJECT = 3,
	//Resources
	MESH = 4,
	SHADER = 5,
	TEXTURE = 6
};
const int numpTypes = 3;