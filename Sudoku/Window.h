#pragma once

#include <iostream>
#include <string>
#include <SDL.h>

class Window {
private:
	const std::string title = "Sudoku";
	const int width = 490;
	const int height = 490;
	bool closed = false;

	SDL_Window* window;

public:
	Window();
	~Window();

	bool init();
	bool isClosed();
	void handleEvents();
};