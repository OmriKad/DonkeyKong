#include <cstring>
#include <iostream>
#include "utils.h"
#include "Board.h"

void Board::reset() {
	for (int i = 0; i < MAX_Y; i++) {
		memcpy(currentBoard[i], originalBoard[i], MAX_X + 1);
	}
}

void Board::print() const {
	for (int i = 0; i < MAX_Y - 1; i++) {
		std::cout << currentBoard[i] << '\n';
	}
	std::cout << currentBoard[MAX_Y - 1];
}

void Board::printLives(short x) const
{
	gotoxy(71, 3);
	std::cout << x;
}

