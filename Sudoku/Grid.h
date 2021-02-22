#pragma once

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
	bool drawStartingGrid = false;
	bool drawSolvedGrid = false;

	void setText(std::unique_ptr<Sudoku>& sudoku, int rowIndex, int columnIndex, int x, int y);

public:
	Grid(SDL_Renderer* _renderer);
	~Grid();

	bool canDraw(std::unique_ptr<Sudoku>& sudoku);
	void drawGrid(std::unique_ptr<Sudoku>& sudoku, std::unique_ptr<Window>& window);
	void drawControls(std::unique_ptr<Window>& window);
	bool isDrawStartingGrid();
	bool isDrawSolvedGrid();
};