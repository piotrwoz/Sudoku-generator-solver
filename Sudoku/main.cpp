#include <memory>
#include "Window.h"
#include "Grid.h"
#include "Sudoku.h"

int main(int argc, char** args) {
	std::unique_ptr<Window> window = std::make_unique<Window>();
	std::unique_ptr<Grid> board(new Grid(window->getRenderer()));

	std::unique_ptr<Sudoku> sudoku = std::make_unique<Sudoku>();
	sudoku->printBoard();

	board->drawGrid(sudoku);
	window->clear();

	while (!window->isClosed()) {
		window->handleEvents();
	}

	return 0;
}