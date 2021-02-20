#include "Sudoku.h"

Sudoku::Sudoku() {
	this->allocateArray2D();
}

Sudoku::~Sudoku() {
	
}

void Sudoku::allocateArray2D() {
	this->board = std::make_unique<std::unique_ptr<int[]>[]>(this->size);
	for (int i = 0; i < this->size; i++) {
		std::unique_ptr<int[]> board_1D = std::make_unique<int[]>(this->size);

		for (int k = 0; k < this->size; k++) {
			board_1D[k] = 0;
		}
		this->board[i] = std::move(board_1D);
	}
}

void Sudoku::printBoard() {
	for (int i = 0; i < this->size; i++) {
		if (i % 3 == 0 && i > 0) {
			std::cout << std::endl << std::endl;
		}

		for (int k = 0; k < this->size; k++) {
			if (k % 3 == 0 && k > 0) {
				std::cout << "  ";
			}

			std::cout << this->board[i][k] << " ";
		}
		
		std::cout << std::endl;
	}
	std::cout << std::endl << std::endl;
}