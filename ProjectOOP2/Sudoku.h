#pragma once
#include "SudokuMatrix.h"
class Sudoku
{
private:
	SudokuMatrix sudokuMatrix;
public:
	SudokuMatrix getMatrix() const;
	bool solve();
	bool findEmptyLocation(int& row, int& col) const;
	bool isSafe(int row, int col, int num) const;
	Sudoku(const std::string& filename);
	Sudoku(const Sudoku& other);
	Sudoku();
	Sudoku(const int& complexity);
	~Sudoku();
	int selfsolving();
	void clear();
	bool isFilledCorrectly();
};

