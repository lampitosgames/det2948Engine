#pragma once
#include <vector>
#include "Handle.h"
#include "pType.h"
#include "ObjectFactory.h"
#include "Render.h"
#include "Physics.h"

using namespace std;

class Scene {
protected:
	bool init = false;
	ObjectFactory* OF;
	Render* RS;
	Physics* PS;
public:
	vector<Handle> objects;

	Scene() {}

	virtual bool Start();
	virtual void Update(float dt);
	virtual void Activate();
};