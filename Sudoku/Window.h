#pragma once

#include <iostream>
#include <string>
#include <SDL.h>

class Window {
private:
	const std::string title = "Sudoku";
	bool closed;

	SDL_Window* window = nullptr;

protected:
	const int width = 500;
	const int height = 500;
	SDL_Renderer* renderer = nullptr;

private:
	bool initSDL();
	bool createWindow();
	bool createRenderer();

public:
	Window();
	~Window();

	bool init();
	bool isClosed();
	void handleEvents();
	void clear();

	SDL_Renderer* getRenderer();
};