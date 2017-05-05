#include "Engine.h"

int main() {
	if (!Engine::Start()) {
		return -1;
	}

	//Game loop
	//Loop until the user closes the window
	Engine::GameLoop();

	return 0;
}