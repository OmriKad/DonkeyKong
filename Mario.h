#pragma once

#include <iostream>
#include <windows.h>
#include "utils.h"
#include "Board.h"

class Mario 
{
	// Some of the class attributes and the movement + board logic was inspired by the code example published my Amir Kirsh.
	static constexpr char keys[] = { 'w', 'a', 'x', 'd', 's' };
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);
	struct Direction { int x, y; }; // inner private struct
	int x = 65, y = 23;
	Direction dir{ 0, 0 }; // current direction: dir.x, dir.y
	short lives = 5;
	bool isAlive = true;
	bool hasWon = false;
	bool isFalling = false;
	short jumpCount = 0;
	int climbDelayCounter = 0;
	int climbDelay = 2;
	short const jumpLimit = 2;
	short fallCount = 0;
	short const fallLimit = 5;
	char ch = '@';
	Board* pBoard = nullptr;
	void draw(char c) const
	{
		gotoxy(x, y);
		std::cout << c;
	}
public:
	int getX() const { return x; }
	int getY() const { return y; }
	void decreaseLife() { lives--; }
	void draw() const
	{
		draw(ch);
	}
	void erase()
	{
		char currentTile = pBoard->getChar(x, y);
		switch (currentTile)
		{
		case 'H':
			draw('H');
			break;
		case '=':
			draw('=');
			break;
		default:
			draw(' ');
			break;
		}
	}

	void keyPressed(char key);
	void move();
	void resetPos() { x = 65; y = 23; }
	bool getIsAlive() const { return isAlive; }
	void setIsAlive(bool b) { isAlive = b; }
	bool getHasWon() const { return hasWon; }
	short getLives() const { return lives; }
	void setBoard(Board& board) { pBoard = &board; }
};
