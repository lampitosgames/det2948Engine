#pragma once

class System {
public:
	virtual bool Start() = 0;

	virtual void Update(float dt) = 0;

	virtual ~System() {}
};