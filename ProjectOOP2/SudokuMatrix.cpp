#include "SudokuMatrix.h"
SudokuMatrix::SudokuMatrix(): rows(9), cols(9)
{
	matrix = new int* [rows];
	for (int i = 0; i < rows; ++i) {
		matrix[i] = new int[cols];
		for (int j = 0; j < cols; ++j)
			matrix[i][j] = 0;
	}
}

SudokuMatrix::~SudokuMatrix()
{
    // Clear the memory, because our object is not simple
	for (int i = 0; i < rows; ++i) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

SudokuMatrix::SudokuMatrix(const string& filename): rows(9), cols(9)
{

	ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "We cannot open the file: " << filename << endl;
        return;
    }
    // Making some space for our matrix in memory
    matrix = new int*[rows]; 
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = new int[cols];
    }
    // Directly reading and writing (">>" reads for one word)
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++)
        {
            file >> matrix[i][j];
        }
    }

    file.close();
}

void SudokuMatrix::setElement(int row, int col, int value)
{
    // Validate the parametrs
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        matrix[row][col] = value;
    }
    else {
        cout << "\n Try again. It's invalid. \n";
    }
}

int SudokuMatrix::getElement(int row, int col) const
{
    // Validate the parametrs
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        return matrix[row][col];
    }
    else {
        return 0;
    }
}

// Functionality to be able to use []
int* SudokuMatrix::operator[](int rowIndex) {
    return matrix[rowIndex];
}
const int* SudokuMatrix::operator[](int rowIndex) const {
    return matrix[rowIndex];
}

void SudokuMatrix::writeToFile(const string& filename) const
{
    ofstream file(filename.c_str());
    if (!file.is_open())
    {
        cerr << "We cannot open the file: " << filename << endl;
        return;
    }

    // Writing our matrix into the file
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            file << matrix[i][j] << " ";
        }
        file << endl;
    }

    file.close();
}
ostream& operator<<(ostream& os, const SudokuMatrix& m)
{
    // Typing our matrix in the console
    if (m.matrix != nullptr) {
        for (int i = 0; i < m.rows; ++i) {
            for (int j = 0; j < m.cols; ++j) {
                os << m.matrix[i][j] << " ";
            }
            os << "\n";
        }
    }
    return os;
}

int** SudokuMatrix::getMatrix() const
{
    return matrix;
}

int SudokuMatrix::getRows() const
{
    return rows;
}

int SudokuMatrix::getCols() const
{
    return cols;
}

SudokuMatrix& SudokuMatrix::operator=(const SudokuMatrix& m)
{
    if (this != &m) { // If this is not one matrix,
        for (int i = 0; i < rows; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
        
        rows = m.rows;
        cols = m.cols;
        matrix = new int* [rows];
        for (int i = 0; i < rows; ++i) {
            matrix[i] = new int[cols];
            for (int j = 0; j < cols; ++j) {
                matrix[i][j] = m.matrix[i][j];
            }
        }
    }
    return *this;
}
// Clear the matrix
void SudokuMatrix::clear()
{
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = 0;
        }
    }
}
// Copy-constructor
SudokuMatrix::SudokuMatrix(const SudokuMatrix& m) : rows(m.rows), cols(m.cols)
{
    matrix = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = m.matrix[i][j];
        }
    }
}
// Counting cells that have been filled
int SudokuMatrix::countFilledCells() const {
    int count = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] != 0) {
                count++;
            }
        }
    }
    return count;
}
// Operator == for tests
bool SudokuMatrix::operator==( const SudokuMatrix& other ) const {
    if ( rows != other.rows || cols != other.cols ) {
        return false; 
    }

    for ( int i = 0; i < rows; ++i ) {
        for ( int j = 0; j < cols; ++j ) {
            if ( matrix[ i ][ j ] != other.matrix[ i ][ j ] ) {
                return false; 
            }
        }
    }

    return true; 
}