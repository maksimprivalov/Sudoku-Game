#include "GameInterface.h"

// Deafult constructor
GameInterface::GameInterface() : sudoku(), wrong_answers(0), games(0)
{
}
// This destrictor will call sudoku's destructor and sudoku's distructor will call sudokuMatrix's destructor
GameInterface::~GameInterface()
{
}
// Game!
GameInterface::GameInterface(char* argv[]) : sudoku(), wrong_answers(0), games(0)
{
    int mode = 0;
    cout << "\nWelcome to the Sudoku game by SV81/2023\n";
    while (true) {
        cout << "\nYou have to choose do you want to solve the task from the file,\nor you want us to generate special random Sudoku board for you! \n Type: \n 0 - if you dont want to play \n 1 - if you want to solve task from the file \n 2 - if you want to solve random one \n";
        cin >> mode;
        //Sudoku sudoku; // Random matrix
        if (mode == 1) {
            // From file
            sudoku = Sudoku(argv[1]);
        }
        else {
            if (mode == 2) {
                // Randomly
                cout << "Choose the complexity level. \n Type:\n 1 - random easy sudoku board for beginners\n 2 - random average sudoku\n 3 - random hard level sudoku\n Any other number to exit\n";
                cin >> mode;
                if (mode == 1) {
                    // Easy sudoku
                    sudoku = Sudoku(8);
                }
                else {
                    if (mode == 2) {
                        // We already have the average sudoku
                    }
                    else {
                        if (mode == 3) {
                            // Hard sudoku
                            sudoku = Sudoku(2);
                        }
                    }
                }
            }
            else {
                break;
            }
        }
        cout << "Your sudoku task is right here:\n" << sudoku.getMatrix() << "\nNext question, captain!\n Do you want to solve this task by yourself or you want us to show the solution?  \n Type: \n 0 - if you dont want to play \n 1 - I want to solve by myself \n 2 - show me the solution \n ";
        cin >> mode;
        if (mode == 1) {
            // By yourfelf
            games++;
            wrong_answers += sudoku.selfsolving();
        }
        else {
            if (mode == 2) {
                games++;
                // Auto-solution
                if (sudoku.solve()) {
                    cout << "\nYour solved sudoku task:" << endl;
                    cout << sudoku.getMatrix();
                }
                else {
                    cout << "\nNo solution found." << endl;
                }
            }
        }
        sudoku.getMatrix().writeToFile(argv[2]); // Write your matrix in the file
        cout << "\nDo you want to play again?\nType 1, if you want to continue\nType any other number, if you want to exit:\n";
        cin >> mode;
        if (mode != 1)
            break;
        sudoku.clear(); // Clear the board
        sudoku = Sudoku();
    }
    cout << "\nIt was impressive! You did just " << wrong_answers << " mistakes in " << games << " games!\n";
}
