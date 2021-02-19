#include <memory>
#include "Window.h"

int main(int argc, char** args) {
	std::unique_ptr<Window> window = std::make_unique<Window>();

	while (!window->isClosed()) {
		window->handleEvents();
	}

	return 0;
}