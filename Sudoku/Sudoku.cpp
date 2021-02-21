#include "Sudoku.h"

Sudoku::Sudoku() {
	srand(time(NULL));

	this->board = this->allocateArray2D();
	this->startingTiles = this->allocateArray2D();
	this->resetBoard();
}

Sudoku::~Sudoku() {
	this->deallocateArray2D(this->board);
	this->deallocateArray2D(this->startingTiles);
}

int** Sudoku::allocateArray2D() {
	int** array = new int* [this->size];
	for (int i = 0; i < this->size; i++) {
		array[i] = new int[this->size];
	}

	return array;
}

void Sudoku::deallocateArray2D(int** array) {
	for (int i = 0; i < this->size; i++) {
		delete[] array[i];
	}
	delete[] array;
}

void Sudoku::resetBoard() {
	for (int i = 0; i < this->size; i++) {
		for (int k = 0; k < this->size; k++) {
			this->board[i][k] = EMPTY_TILE;
		}
	}
}

void Sudoku::generate(int mode) {
	this->copyFromOriginalBoard();
	this->shuffle();
	std::cout << "After shuffle" << std::endl;
	this->printBoard();
	this->removeTiles(mode);
	this->setStartingTiles();
	std::cout << "After removing some tiles" << std::endl;
	this->printBoard();
}

void Sudoku::copyFromOriginalBoard() {
	for (int i = 0; i < this->size; i++) {
		for (int k = 0; k < this->size; k++) {
			this->board[i][k] = this->originalBoard[i][k];
		}
	}
}

std::unique_ptr<std::unique_ptr<int[]>[]> Sudoku::createTmpBoardCopy() {

	std::unique_ptr<std::unique_ptr<int[]>[]> copy = std::make_unique<std::unique_ptr<int[]>[]>(this->size);
	for (int i = 0; i < this->size; i++) {
		std::unique_ptr<int[]> board_1D = std::make_unique<int[]>(this->size);
		copy[i] = std::move(board_1D);
	}

	for (int i = 0; i < this->size; i++) {
		for (int k = 0; k < this->size; k++) {
			copy[i][k] = this->board[i][k];
		}
	}

	return copy;
}

void Sudoku::shuffle() {
	const int swapsAmount = pow(2, 12);
	for (int i = 0; i < swapsAmount; i++) {
		// one of three options: flip board horizontally, flip board vertically or don't flip
		int flipMode = rand() % 3;
		if (flipMode == FLIP_HORIZONTALLY) {
			this->flipBoardHorizontally();
		}
		else if (flipMode == FLIP_VERTICALLY) {
			this->flipBoardVertically();
		}

		// swap rows or columns
		int swapMode = rand() % 2;
		if (swapMode == SWAP_ROWS) {
			this->swapRandomRows();
		}
		else {
			this->swapRandomCols();
		}
	}
}

void Sudoku::swapRandomRows() {
	int squareRow = rand() % this->squareSize;
	int rowIndex1, rowIndex2;
	do {
		rowIndex1 = rand() % this->squareSize;
		rowIndex2 = rand() % this->squareSize;
	} while (rowIndex1 == rowIndex2);

	if (squareRow == MIDDLE_SQUARES) {
		rowIndex1 += this->squareSize;
		rowIndex2 += this->squareSize;
	}
	else if (squareRow == LOWER_SQUARES) {
		rowIndex1 += 2 * this->squareSize;
		rowIndex2 += 2 * this->squareSize;
	}

	this->swapRows(rowIndex1, rowIndex2);
}

void Sudoku::swapRows(int rowIndex1, int rowIndex2) {
	int* buffer = this->board[rowIndex1];
	this->board[rowIndex1] = this->board[rowIndex2];
	this->board[rowIndex2] = buffer;
}

void Sudoku::swapRandomCols() {
	transposeBoard();
	this->swapRandomRows();
	transposeBoard();
}

void Sudoku::transposeBoard() {
	std::unique_ptr<std::unique_ptr<int[]>[]> copy = this->createTmpBoardCopy();

	for (int i = 0; i < this->size; i++) {
		for (int k = 0; k < this->size; k++) {
			this->board[i][k] = copy[k][i];
		}
	}
}

void Sudoku::flipBoardHorizontally() {
	int i = 0;
	int k = this->size - 1;

	while (i < this->size / 2) {
		this->swapRows(i, k);

		i++;
		k--;
	}
}

void Sudoku::flipBoardVertically() {
	this->transposeBoard();
	this->flipBoardHorizontally();
	this->transposeBoard();
}

bool Sudoku::checkIfSafe(int** grid, int rowIndex, int columnIndex, int number) {
	int squareIndexRowBegin = rowIndex - rowIndex % this->squareSize;
	int squareIndexColumnBegin = columnIndex - columnIndex % this->squareSize;

	if (this->checkNumberNotUsedInRow(grid, rowIndex, columnIndex, number) &&
		this->checkNumberNotUsedInColumn(grid, rowIndex, columnIndex, number) &&
		this->checkNumberNotUsedInSquare(grid, rowIndex, columnIndex, squareIndexRowBegin, squareIndexColumnBegin, number)) {

		return true;
	}
	else {
		return false;
	}
}

bool Sudoku::checkNumberNotUsedInRow(int** grid, int rowIndex, int columnIndex, int number) {
	for (int i = 0; i < this->size; i++) {
		if (number == grid[rowIndex][i]) {
			return false;
		}
	}

	return true;
}

bool Sudoku::checkNumberNotUsedInColumn(int** grid, int rowIndex, int columnIndex, int number) {
	for (int i = 0; i < this->size; i++) {
		if (number == grid[i][columnIndex]) {
			return false;
		}
	}

	return true;
}

bool Sudoku::checkNumberNotUsedInSquare(int** grid, int rowIndex, int columnIndex, int rowIndexBegin, int columnIndexBegin, int number) {
	for (int i = 0; i < this->squareSize; i++) {
		for (int k = 0; k < this->squareSize; k++) {
			if (number == grid[rowIndexBegin + i][columnIndexBegin + k] && number != grid[rowIndex][columnIndex]) {
				return false;
			}
		}
	}

	return true;
}

void Sudoku::removeTiles(int mode) {
	for (int i = 0; i < this->size; i += this->squareSize) {
		for (int k = 0; k < this->size; k += this->squareSize) {
			int elementsToRemoveAmount = this->determineAmountOfTilesToRemove(mode);
			this->removeTilesFromSquare(i, k, elementsToRemoveAmount);
		}
	}
}

void Sudoku::setStartingTiles() {
	for (int i = 0; i < this->size; i++) {
		for (int k = 0; k < this->size; k++) {
			if (this->board[i][k] != EMPTY_TILE) {
				this->startingTiles[i][k] = STARTING_NON_EMPTY_TILE;
			}
			else {
				this->startingTiles[i][k] = STARTING_EMPTY_TILE;
			}
		}
	}
}

int Sudoku::determineAmountOfTilesToRemove(int mode) {
	int elementsToRemoveAmount;
	if (mode == EASY_MODE) {
		// 3 or 4
		elementsToRemoveAmount = rand() % 2 + 3;
	}
	else if (mode == NORMAL_MODE) {
		// 4, 5 or 6
		elementsToRemoveAmount = rand() % 3 + 4;
	}
	else {
		// 6 or 7
		elementsToRemoveAmount = rand() % 2 + 6;
	}

	return elementsToRemoveAmount;
}

void Sudoku::removeTilesFromSquare(int rowIndexBegin, int columnIndexBegin, int toRemoveAmount) {
	int iterator = 0;
	while(iterator < toRemoveAmount) {
		int i = rand() % this->squareSize;
		int k = rand() % this->squareSize;

		if (this->board[i + rowIndexBegin][k + columnIndexBegin] == EMPTY_TILE) {
			continue;
		}

		this->board[i + rowIndexBegin][k + columnIndexBegin] = EMPTY_TILE;
		iterator++;
	}

}

void Sudoku::solve() {
	if (!this->backtracking(this->board)) {
		std::cout << "There is no solution for this sudoku" << std::endl;
	}
	else {
		this->solved = true;
		std::cout << "SOLUTION" << std::endl;
		this->printBoard();
	}
}

bool Sudoku::backtracking(int** grid) {
	int rowIndex, columnIndex;

	if (!this->findNextEmptyTile(grid, rowIndex, columnIndex)) {
		// there is no empty tiles, so there is a solution of sudoku
		return true;
	}

	for (int number = 1; number <= this->size; number++) {
		if (this->checkIfSafe(grid, rowIndex, columnIndex, number)) {
			grid[rowIndex][columnIndex] = number;

			if (this->backtracking(grid)) {
				return true;
			}

			grid[rowIndex][columnIndex] = EMPTY_TILE;
		}
	}

	return false;
}

bool Sudoku::findNextEmptyTile(int** grid, int& rowIndex, int& columnIndex) {
	for (rowIndex = 0; rowIndex < this->size; rowIndex++) {
		for (columnIndex = 0; columnIndex < this->size; columnIndex++) {
			if (grid[rowIndex][columnIndex] == EMPTY_TILE) {
				return true;
			}
		}
	}

	return false;
}

void Sudoku::printBoard() {
	for (int i = 0; i < this->size; i++) {
		if (i % 3 == 0 && i > 0) {
			std::cout << std::endl;
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

int Sudoku::getSize() {
	return this->size;
}

int** Sudoku::getBoard() {
	return this->board;
}

int** Sudoku::getStartingTiles() {
	return this->startingTiles;
}

bool Sudoku::isSolved() {
	return this->solved;
}