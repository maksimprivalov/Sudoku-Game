#include "Sudoku.h"

// Constructor with parameter string& filename. From this constructor we call the same one on sudokuMatrix field to fill the sudokuMatrix
Sudoku::Sudoku(const string& filename) : sudokuMatrix(filename)
{
}
// Constructor with parameter Sudoku& other. From this constructor we call the same one (SudokuMatrix& other) on sudokuMatrix field to fill the sudokuMatrix
Sudoku::Sudoku(const Sudoku& other) : sudokuMatrix(other.sudokuMatrix)
{
}
Sudoku::Sudoku() : sudokuMatrix()
{
    // Generating some values on our board
    srand(time(0));
    int m = rand() % 2; // Add more random variations
    for (int i = m; i < sudokuMatrix.getRows(); i += 2) {
        for (int j = m; j < sudokuMatrix.getCols(); j += 2) {
            int randomNumber;
            do {
                randomNumber = 1 + rand() % 9;
            } while (!isSafe(i, j, randomNumber)); // We use this loop because in this case it's safe to use it. We will not have enough numbers to make infinitive loop

            sudokuMatrix.setElement(i,j, randomNumber);
        }
    }
    // Solve the matrix. We need to solve it to generate more random sudoku game
    solve();
    // We are gonna delete ~1/2 of all variables
    for (int i = 0; i < 9*9/2; ++i) {
        int row = rand() % sudokuMatrix.getRows();
        int col = rand() % sudokuMatrix.getCols();

        // We should not delete 0s
        while (sudokuMatrix.getElement(row, col) == 0) {
            row = rand() % sudokuMatrix.getRows();
            col = rand() % sudokuMatrix.getCols();
        }

        sudokuMatrix.setElement(row, col, 0);
    }
}
// Constructor with complexity argument (for complexity of levels)
Sudoku::Sudoku(const int& complexity) : sudokuMatrix()
{
    // Generating some values on our board
    srand(time(0));
    int m = rand() % 2; // Add more random variations
    for (int i = m; i < sudokuMatrix.getRows(); i += 2) {
        for (int j = m; j < sudokuMatrix.getCols(); j += 2) {
            int randomNumber;
            do {
                randomNumber = 1 + rand() % 9;
            } while (!isSafe(i, j, randomNumber)); // We use this loop because in this case it's safe to use it. We will not have enough numbers to make infinitive loop

            sudokuMatrix.setElement(i, j, randomNumber);
        }
    }
    // Solve the matrix. We need to solve it to generate more random sudoku game
    solve();
    // We are gonna delete some variables
    for (int i = 0; i < 9 * 9 / ((complexity == 2) ? 1.5 : complexity); ++i) {
        int row = rand() % sudokuMatrix.getRows();
        int col = rand() % sudokuMatrix.getCols();

        // We should not delete 0s
        while (sudokuMatrix.getElement(row, col) == 0) {
            row = rand() % sudokuMatrix.getRows();
            col = rand() % sudokuMatrix.getCols();
        }

        sudokuMatrix.setElement(row, col, 0);
    }
}
// Destructor. It will automatically call the destructor of sudokuMatrix field.
Sudoku::~Sudoku()
{
}
// If we would like to clear the board
void Sudoku::clear() 
{
    sudokuMatrix.clear();
}
// Main method for self solving
int Sudoku::selfsolving()
{
    Sudoku task(*this); // Saving original board
    int row, col, value; 
    int r, c; // We have to create them to use findEmptyLocation(row, col) method. We dont want to create new one.
    int mode = 0; // For the answers
    int wrong_answers_counter = 0; // Counter of the wrong answers (valid ones)
    cout << "Time for solving! Good luck :)\n";
    while (findEmptyLocation(r, c)) { // While we have 0s
        cout << "Your board:" << endl << this->sudokuMatrix << endl; // Current board
        cout << "This is your current matrix. As always, you have many options. Type:\n 1 -  If you want to fill the cell (also you can fill it with 0) \n 2 - if you want to check original board \n 3 - solve automatically this version \n 0 - exit\n";
        cin >> mode;
        if (mode == 1) {
            while (true) {
                cout << "Type the cell in format 'row col value'. Make sure you counting from 0. E.g.: 1 2 9 \n Type '-1' if you want to go back \n";
                cin >> row;
                if (row == -1) // User wants to go back
                    break;
                cin >> col >> value;
                if (!(value <= 9 && value >= 0 && row >= 0 && row < 9 && col >= 0 && col < 9)) { // Validation
                    cout << "\n Try again. It's invalid. \n";
                }
                else {
                    if (!(isSafe(row, col, value)) && value != 0) { // Validation 2: rules. We don't have the rools on 0's, except rule ¹3
                        cout << "\n Try again. Follow the rules of sudoku! \n";
                        wrong_answers_counter++; // We make it +=1 just here because in other cases we have just invalid answers.
                    }
                    else {
                        if (task.getMatrix()[row][col] != 0) { // Validation 3: root matrix
                            cout << "\n You are trying to fill the cell that has been in the Task!!!\n";
                        }
                        else {
                            sudokuMatrix.setElement(row, col, value); // If all is ok filling and countinue 
                            break;
                        }
                    }
                }
            }
        }
        else {
            if (mode == 2) {
                cout << "Original task-board:" << endl << task.sudokuMatrix << endl;
            }
            else {
                if (mode == 3) {
                    if (solve()) {
                        // Now it's our business :)
                        cout << "\nYour solved sudoku:\n" << sudokuMatrix << endl;
                    }
                    else {
                        cout << "\nWe can't solve this sudoku (at least your current version)\n";
                    }
                    break; // Exit
                }
                else {
                    if (mode == 0) {
                        break; // Exit
                    }
                    else {
                        cout << "Invalod operation. Type 0-3.\n";
                    }
                }
            }
        }
    }
    return wrong_answers_counter;
}
SudokuMatrix Sudoku::getMatrix() const
{
    return sudokuMatrix;
}

bool Sudoku::solve() {
    int row, col; // findEmptyLocation(row, col) will initialize them every time it find the 0 cell
    if (!findEmptyLocation(row, col)) { // If !findEmptyLocation(row, col) == true then we don't have free cells (puzzle is silved)
        return true;
    }

    for (int num = 1; num <= sudokuMatrix.getCols(); ++num) { // Going from 1 to 9
        if (isSafe(row, col, num)) { // Check
            sudokuMatrix.setElement(row, col, num);

            if (solve()) { // Recursion. If the puzzle is solved with the current number, return true
                return true;
            }

            sudokuMatrix.setElement(row, col, 0); // If the current number doesn't lead to a solution, backtrack.
        }
    }

    // No valid number found, backtrack
    return false;
}

bool Sudoku::findEmptyLocation(int& row, int& col) const {
    for (row = 0; row < sudokuMatrix.getRows(); ++row) {
        for (col = 0; col < sudokuMatrix.getCols(); ++col) {
            if (sudokuMatrix.getElement(row, col) == 0) {
                return true; // Found an empty location
            }
        }
    }

    return false; // No empty location found
}

bool Sudoku::isSafe(int row, int col, int num) const {

    for (int i = 0; i < sudokuMatrix.getCols(); ++i) {
        if (sudokuMatrix.getElement(row, i) == num || sudokuMatrix.getElement(i, col) == num) { // Check if 'num' is not in the current row and column
            return false;
        }
    }

    int submatrixStartRow = row - row % 3;
    int submatrixStartCol = col - col % 3;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (sudokuMatrix.getElement(submatrixStartRow + i, submatrixStartCol + j) == num) { // Check if 'num' is not in the current 3x3 submatrix
                return false;
            }
        }
    }

    return true; // 'num' is safe to place in the current position
}
// Checking is our matrix filled correctly (for tests)
bool Sudoku::isFilledCorrectly ( ) {
    for ( int i = 0; i < sudokuMatrix.getCols ( ); ++i ) {
        for ( int j = 0; j < sudokuMatrix.getCols ( ); ++j ) {
            int currentValue = sudokuMatrix.getMatrix ( )[ i ][ j ];
            if (!(isSafe(i,j,currentValue)))
                return false;
        }
    }
    return true;
}