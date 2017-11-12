#include "Engine.h"
#include "Model.h"

#include <iostream>

int main() {
	Engine engine = Engine();

	if (engine.init()) {
		engine.update();
		engine.stop();

		return 0;
	}

	std::cin.clear();
	std::cout << "Press enter to continue...";
	std::cin.get();
	return -1;
}