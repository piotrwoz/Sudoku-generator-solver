#include "Window.h"

Window::Window() {
	this->closed = !this->init();
}

Window::~Window() {
	SDL_DestroyWindow(this->window);
	SDL_DestroyRenderer(this->renderer);
	TTF_Quit();
	SDL_Quit();
}

bool Window::initSDL() {
	// SDL_Init returns 0 if initialization succeed
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "There was a problem with SDL initialization" << std::endl;
		return false;
	}

	return true;
}

bool Window::initFonts() {
	if (TTF_Init() == -1) {
		std::cout << "There was a problem with fonts initialization" << std::endl;
		return false;
	}

	return true;
}

bool Window::createWindow() {
	this->window = SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, 0);
	if (this->window == nullptr) {
		std::cout << "Failed to create window" << std::endl;
		return false;
	}

	return true;
}

bool Window::createRenderer() {
	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_PRESENTVSYNC);
	if (this->renderer == nullptr) {
		std::cout << "Failed to create renderer" << std::endl;
		return false;
	}

	return true;
}

bool Window::init() {
	if (!this->initSDL() || !this->initFonts() || !this->createWindow() || !this->createRenderer()) {
		return false;
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

			case SDL_KEYDOWN: {
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE: {
						this->closed = true;
					}
					default: {
						break;
					}
				}
			}
				
			case SDL_MOUSEBUTTONUP: {
				int x, y;
				SDL_GetMouseState(&x, &y);
				std::cout << "x = " << x << " | y = " << y << std::endl;
				
				break;
			}

			default: {
				break;
			}
		}
	}
}

void Window::clear() {
	const int red = 0;
	const int green = 0;
	const int blue = 0;
	const int alpha = 0;

	SDL_RenderPresent(this->renderer);
	SDL_SetRenderDrawColor(this->renderer, red, green, blue, alpha);
	SDL_RenderClear(this->renderer);
}

SDL_Renderer* Window::getRenderer() {
	return this->renderer;
}