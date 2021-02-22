#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Text.h"
#include "Sudoku.h"

class Window {
private:
	const std::string title = "Sudoku";
	bool closed;
	std::pair<int, int> mouseClickCoords;

	SDL_Window* window = nullptr;

protected:
	const int width = 500;
	const int height = 600;
	SDL_Renderer* renderer = nullptr;

private:
	bool initSDL();
	bool initFonts();
	bool createWindow();
	bool createRenderer();

public:
	Window();
	~Window();

	bool init();
	bool isClosed();
	void handleEvents(std::unique_ptr<Sudoku>& sudoku);
	void clear();

	SDL_Renderer* getRenderer();
	int getWidth();
	int getHeight();
};