#pragma once
#include "Sudoku.h"
class GameInterface
{
private:
	Sudoku sudoku;
	int wrong_answers;
	int games;
public:
	GameInterface();
	~GameInterface();
	GameInterface(char* argv[]);
};

