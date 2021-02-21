#pragma once

#define SIZE 9
#define SWAP_ROWS 0
#define SWAP_COLS 1
#define UPPER_SQUARES 0
#define MIDDLE_SQUARES 1
#define LOWER_SQUARES 2
#define FLIP_HORIZONTALLY 1
#define FLIP_VERTICALLY 2
#define EASY_MODE 0
#define NORMAL_MODE 1
#define HARD_MODE 2
#define EMPTY_TILE 0
#define STARTING_EMPTY_TILE 0
#define STARTING_NON_EMPTY_TILE 1


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
	int** startingTiles = nullptr;

	int** allocateArray2D();
	void deallocateArray2D(int** arr);
	void resetBoard();
	void copyFromOriginalBoard();
	std::unique_ptr<std::unique_ptr<int[]>[]> createTmpBoardCopy();
	void check();
	void shuffle();

	void swapRandomRows();
	void swapRows(int rowIndex1, int rowIndex2);
	void swapRandomCols();
	void transposeBoard();
	void flipBoardHorizontally();
	void flipBoardVertically();
	bool checkNumberNotUsedInRow(int** grid, int rowIndex, int columnIndex, int number);
	bool checkNumberNotUsedInColumn(int** grid, int rowIndex, int columnIndex, int number);
	bool checkNumberNotUsedInSquare(int** grid, int rowIndex, int columnIndex, int rowIndexBegin, int columnIndexBegin, int number);
	bool checkIfSafe(int** grid, int rowIndex, int columnIndex, int number);
	void removeTiles(int mode);
	void setStartingTiles();
	int determineAmountOfTilesToRemove(int mode);
	void removeTilesFromSquare(int rowIndexBegin, int columnIndexBegin, int toRemoveAmount);
	bool backtracking(int** grid);
	bool findNextEmptyTile(int** grid, int& rowIndex, int& columnIndex);

public:
	Sudoku();
	~Sudoku();

	void generate(int mode);
	void solve();
	void printBoard();
	int getSize();
	int** getBoard();
	int** getStartingTiles();
};