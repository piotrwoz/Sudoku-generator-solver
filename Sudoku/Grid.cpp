#include "Grid.h"

Grid::Grid(SDL_Renderer* _renderer){
	this->renderer = _renderer;
}

Grid::~Grid() {
	
}

void Grid::drawGrid(std::unique_ptr<Sudoku>& sudoku) {
	int size = sudoku->getSize();

	int x = this->borderWidth;
	int y = this->borderWidth;

	for (int i = 0; i < this->tilesAmount; i++) {
		for (int k = 0; k < this->tilesAmount; k++) {
			SDL_Rect rect;

			rect.w = this->tileSize;
			rect.h = this->tileSize;
			rect.x = x;
			rect.y = y;

			SDL_SetRenderDrawColor(this->renderer, this->red, this->green, this->blue, this->alpha);
			SDL_RenderFillRect(this->renderer, &rect);

			this->setText(sudoku, i, k, x, y);
			
			x += (this->tileSize + this->borderWidth);
		}

		x = this->borderWidth;
		y += (this->tileSize + this->borderWidth);
	}
}

void Grid::setText(std::unique_ptr<Sudoku>& sudoku, int rowIndex, int columnIndex, int x, int y) {
	int** board = sudoku->getBoard();
	int** startingTiles = sudoku->getStartingTiles();

	std::string fontPath = "fonts/arialbd.ttf";
	const int fontSize = 20;
	SDL_Color black = { 0,0,0,0 };
	SDL_Color red = { 255,0,0,0 };

	std::string number = std::to_string(board[rowIndex][columnIndex]);
	if (startingTiles[rowIndex][columnIndex] == STARTING_NON_EMPTY_TILE) {
		Text* text = new Text(this->renderer, fontPath, fontSize, number, black);

		if (text != nullptr) {
			text->display(x + this->tileSize / 3, y + this->tileSize / 3);
		}

		delete text;
	}
	else if (startingTiles[rowIndex][columnIndex] == STARTING_EMPTY_TILE) {
		Text* text = new Text(this->renderer, fontPath, fontSize, number, red);

		if (text != nullptr) {
			text->display(x + this->tileSize / 3, y + this->tileSize / 3);
		}

		delete text;
	}
}