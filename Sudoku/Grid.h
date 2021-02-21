#pragma once

#include "Window.h"
#include "Sudoku.h"
#include "Text.h"

class Grid {
private:
	SDL_Renderer* renderer = nullptr;
	const int tilesAmount = 9;
	const int tileSize = 50;
	const int borderWidth = 5;
	const int red = 255;
	const int green = 255;
	const int blue = 255;
	const int alpha = 255;

	void setText(std::unique_ptr<Sudoku>& sudoku, int rowIndex, int columnIndex, int x, int y);

public:
	Grid(SDL_Renderer* _renderer);
	~Grid();

	void drawGrid(std::unique_ptr<Sudoku>& sudoku);
};