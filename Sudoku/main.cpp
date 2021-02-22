#include <memory>
#include "Window.h"
#include "Grid.h"
#include "Sudoku.h"

int main(int argc, char** args) {
	std::unique_ptr<Window> window = std::make_unique<Window>();
	std::unique_ptr<Grid> grid(new Grid(window->getRenderer()));
	std::unique_ptr<Sudoku> sudoku = std::make_unique<Sudoku>();
	sudoku->generate();

	while (!window->isClosed()) {
		window->handleEvents(sudoku);

		if (grid->canDraw(sudoku)) {
			grid->drawGrid(sudoku, window);
			window->clear();
		}	
	}

	return 0;
}