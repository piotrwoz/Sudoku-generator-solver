#pragma once

#define SIZE 9
#define SWAP_ROWS 0
#define SWAP_COLS 1
#define UPPER_SQUARES 0
#define MIDDLE_SQUARES 1
#define LOWER_SQUARES 2


#include <iostream>
#include <time.h>
#include <cmath>
#include <memory>

class Sudoku {
private:
	const int size = SIZE;
	const int squareSize = sqrt(this->size);
	int originalBoard[SIZE][SIZE] = {
		8,2,7,1,5,4,3,9,6,
		9,6,5,3,2,7,1,4,8,
		3,4,1,6,8,9,7,5,2,
		5,9,3,4,6,8,2,7,1,
		4,7,2,5,1,3,6,8,9,
		6,1,8,9,7,2,4,3,5,
		7,8,6,2,3,5,9,1,4,
		1,5,4,7,9,6,8,2,3,
		2,3,9,8,4,1,5,6,7
	};
	int** board = nullptr;

	void createSetOfAllPossibleNumbers();
	int** allocateBoard();
	void deallocateBoard();
	void resetBoard();
	void copyFromOriginalBoard();
	std::unique_ptr<std::unique_ptr<int[]>[]> createBoardCopy();
	void generate();
	void check();
	void shuffle();

	void swapRows();
	void swapCols();
	void transposeBoard();

	bool checkNumberNotUsedInRow(int rowIndex, int columnIndex, int number);
	bool checkNumberNotUsedInColumn(int rowIndex, int columnIndex, int number);
	bool checkNumberNotUsedInSquare(int rowIndex, int columnIndex, int rowIndexBegin, int columnIndexBegin, int number);
	bool checkIfSafe(int rowIndex, int columnIndex, int number);


public:
	Sudoku();
	~Sudoku();

	void printBoard();
	int getSize();
	int** getBoard();
};