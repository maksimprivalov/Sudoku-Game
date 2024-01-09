#pragma once
#include <iostream>
#include <fstream>
using namespace std;
class SudokuMatrix
{
private:
	int** matrix;
	int rows;
	int cols;
public:
	SudokuMatrix();
	~SudokuMatrix();
	SudokuMatrix(const string& filename);
	void setElement(int row, int col, int value);
	int getElement(int row, int col) const;
	int* operator[](int rowIndex);
	const int* operator[](int rowIndex) const;
	friend ostream& operator<<(ostream& os, const SudokuMatrix& matrix);
	int countFilledCells() const;
	void writeToFile(const string& filename) const;
	int** getMatrix() const;
	int getRows() const;
	int getCols() const;
	SudokuMatrix(const SudokuMatrix& other);
    SudokuMatrix& operator=(const SudokuMatrix& other);
	void clear();
	bool operator==( const SudokuMatrix& other ) const;
};

