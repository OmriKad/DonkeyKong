#include <cstring>
#include <iostream>

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

bool Board::is_pos_legal(int x, int y)
{
	char item = this->getChar(x, y);
	return item != 'Q' && item != '=' && item != '>' && item != '<';
}

bool Board::is_ground(int x, int y)
{
	return this->getChar(x, y) == ' ' ? false : true;
}
