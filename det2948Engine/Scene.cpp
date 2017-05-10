#include "Scene.h"
#include "Engine.h"
#include "GameObject.h"

bool Scene::Start() {
	OF = &Engine::OF;
	RS = &Engine::renderSys;
	PS = &Engine::physicsSys;
	return true;
}

void Scene::Update(float dt) {
	if (!this->init && dt <= 0.06) {
		Activate();
	}
}

void Scene::Activate() {
	for (int i = 0; i < objects.size(); i++) {
		Engine::OF.Get<GameObject*>(objects[i])->SetActive(true);
	}
}
