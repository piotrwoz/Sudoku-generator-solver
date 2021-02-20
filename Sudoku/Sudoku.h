#pragma once

#include <iostream>
#include <memory>

class Sudoku {
private:
	const int size = 9;
	std::unique_ptr<std::unique_ptr<int[]>[]> board = nullptr;

	void allocateArray2D();

public:
	Sudoku();
	~Sudoku();

	void printBoard();
};