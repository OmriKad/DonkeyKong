#pragma once
#include "Board.h"
#include "Barrel.h"
#include <vector>
// This class and methods was adapted using CoPilot.
class DonkeyKong
{
	int x;
	int y;
	char ch = '&';
	Board* pBoard = nullptr;
	std::vector<Barrel>* pBarrels = nullptr;

	void draw() const;
	void erase() const;

public:
	void setBoard(Board& board) { pBoard = &board; }
	void setBarrels(std::vector<Barrel>& barrels) { pBarrels = &barrels; }
	void setDonkeyLoc(int x, int y) { this->x = x; this->y = y; }
	void throwBarrel();
	void update();
};
