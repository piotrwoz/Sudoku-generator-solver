#include "Grid.h"

Grid::Grid(SDL_Renderer* _renderer){
	this->renderer = _renderer;
}

Grid::~Grid() {
	
}

void Grid::drawGrid(std::unique_ptr<Sudoku>& sudoku) {
	int size = sudoku->getSize();
	int** board = sudoku->getBoard();

	std::string fontPath = "fonts/arialbd.ttf";
	int fontSize = 20;
	SDL_Color black = { 0,0,0,0 };

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

			std::string number = std::to_string(board[i][k]);
			Text* text = new Text(this->renderer, fontPath, fontSize, number, black);
			if (text != nullptr) {
				text->display(x + this->tileSize / 3, y + this->tileSize / 3);
			}
			delete text;

			x += (this->tileSize + this->borderWidth);
		}

		x = this->borderWidth;
		y += (this->tileSize + this->borderWidth);
	}
}