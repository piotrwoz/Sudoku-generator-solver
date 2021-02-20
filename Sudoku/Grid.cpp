#include "Grid.h"

Grid::Grid(SDL_Renderer* _renderer){
	this->renderer = _renderer;
}

Grid::~Grid() {
	
}

void Grid::drawGrid() {
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

			x += (this->tileSize + this->borderWidth);
		}

		x = this->borderWidth;
		y += (this->tileSize + this->borderWidth);
	}
}