#include "Component.h"
#include "Engine.h"

GameObject* Component::GetGameObject() {
	return Engine::OF.Get<GameObject*>(gameObject);
}
