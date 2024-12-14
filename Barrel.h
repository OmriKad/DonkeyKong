#pragma once
#include "board.h"
#include <iostream>
#include "utils.h"
#include <windows.h>
class Barrel
{
	struct Direction { int x, y; }; // inner private struct
	Direction dir{ 0, 0 }; // current direction: dir.x, dir.y
	char underChar = ' ';
	int lastDirX = 0;
	int x = 18, y = 3;
	bool needToExploade = false;
	bool exploded = false;
	short fallCount = 0;
	short const fallLimit = 8;
	char ch = 'O';
	Board* pBoard = nullptr;
	void draw(char c) const
	{
		gotoxy(x, y);
		std::cout << c;
	}
public:
	void updateBoardPosition(char c)
	{
		// Update the currentBoard array with the character 'c' at the barrel's position
		pBoard->setCharAt(x, y, c);
	}
	void draw()
	{
		underChar = pBoard->getChar(x, y);
		updateBoardPosition(ch);
		draw(ch);
	}
	void erase()
	{
		updateBoardPosition(underChar);
		draw(underChar);
	}
	void move();
	void setBoard(Board& board) { pBoard = &board; }
	bool getNeedToExploade() const { return needToExploade; }
	void setNeedToExploade(bool value) { needToExploade = value; }
	void setDir(int x, int y) { dir.x = x; dir.y = y; }
	void addFallCount() { fallCount++; }
	void resetFallCount() { fallCount = 0; }
	short getFallCount() const { return fallCount; }
	short getFallLimit() const { return fallLimit; }
	void updateXY() { x += dir.x; y += dir.y; }
	void explode() { setExploded(true); ch = '*'; draw(); Sleep(100); erase(); }
	void setLastDirX(int value) { lastDirX = value; }
	int getLastDirX() const { return lastDirX; }
	void setExploded(bool value) { exploded = value; }
	bool getExploded() const { return exploded; }
};