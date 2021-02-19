#include "Window.h"

Window::Window() {
	if (!this->init()) {
		this->closed = true;
	}
}

Window::~Window() {
	SDL_DestroyWindow(this->window);
	SDL_Quit();
	std::cout << "Window has been destroyed" << std::endl;
}

bool Window::init() {

	// SDL_Init returns 0 if initialization succeed
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "There was a problem with SDL initialization" << std::endl;
		return false;
	}
	
	this->window = SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, 0);
	if (this->window == nullptr) {
		std::cout << "Failed to create window" << std::endl;
		return 0;
	}

	return true;
}

bool Window::isClosed() {
	return this->closed;
}

void Window::handleEvents() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {

		switch (event.type) {
			case SDL_QUIT: {
				this->closed = true;
				break;
			}
			default: {
				break;
			}
		}
	}
}