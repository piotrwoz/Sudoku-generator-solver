#include "Grid.h"

Grid::Grid(SDL_Renderer* _renderer) {
	this->renderer = _renderer;
}

Grid::~Grid() {

}

bool Grid::canDraw(std::unique_ptr<Sudoku>& sudoku) {
	if (!sudoku->isSolved() && !this->drawStartingGrid) {
		this->drawStartingGrid = true;
		return true;
	}
	else if (sudoku->isSolved() && !this->drawSolvedGrid) {
		this->drawSolvedGrid = true;
		return true;
	}
	else {
		return false;
	}
}

void Grid::drawGrid(std::unique_ptr<Sudoku>& sudoku, std::unique_ptr<Window>& window) {
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

	this->drawControls(sudoku, window);
}

void Grid::setText(std::unique_ptr<Sudoku>& sudoku, int rowIndex, int columnIndex, int x, int y) {
	int** board = sudoku->getBoard();
	int** startingTiles = sudoku->getStartingTiles();

	std::string fontPath = "fonts/arialbd.ttf";
	const int fontSize = 20;
	SDL_Color black = { 0,0,0,0 };
	SDL_Color red = { 255,0,0,0 };

	std::string number = std::to_string(board[rowIndex][columnIndex]);
	if (startingTiles[rowIndex][columnIndex] == STARTING_NON_EMPTY_TILE && number != "0") {
		std::unique_ptr<Text> text(new Text(this->renderer, fontPath, fontSize, number, black));
		text->display(x + this->tileSize / 3, y + this->tileSize / 3);
	}
	else if (startingTiles[rowIndex][columnIndex] == STARTING_EMPTY_TILE && number != "0") {
		std::unique_ptr<Text> text(new Text(this->renderer, fontPath, fontSize, number, red));
		text->display(x + this->tileSize / 3, y + this->tileSize / 3);
	}
}

void Grid::drawControls(std::unique_ptr<Sudoku>& sudoku, std::unique_ptr<Window>& window) {
	std::string message;
	if (sudoku->isSolved()) {
		message = "SUDOKU HAS BEEN SOLVED";
	}
	else {
		message = "PRESS 'SPACE' TO SOLVE";
	}
	std::string fontPath = "fonts/arialbd.ttf";
	const int fontSize = 32;
	SDL_Color white = { 255,255,255,0 };

	std::unique_ptr<Text> text(new Text(this->renderer, fontPath, fontSize, message, white));
	int width = 0;
	int height = 0;
	int textSize = TTF_SizeText(text->getFont(), message.c_str(), &width, &height);

	int x = window->getWidth() / 2 - width / 2;
	int y = window->getHeight() - height * 2;

	text->display(x, y);
}

bool Grid::isDrawStartingGrid() {
	return this->drawStartingGrid;
}

bool Grid::isDrawSolvedGrid() {
	return this->drawSolvedGrid;
}