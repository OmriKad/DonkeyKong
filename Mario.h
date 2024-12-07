#pragma once

#include <iostream>
#include <windows.h>
#include "utils.h"
#include "Board.h"

class Mario {
	static constexpr char keys[] = { 'w', 'a', 'x', 'd', 's'};
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);
	struct Direction { int x, y; }; // inner private struct
	int x = 65, y = 23;
	Direction dir{0, 0}; // current direction: dir.x, dir.y
	char lives = 5;
	bool isAlive = true;
	bool canJump = true;
	short jumpCount = 0;
	short const jumpLimit = 2;
	short fallCount = 0;
	short const fallLimit = 5;
	char isClimbing = 0;
	bool endOfLadder = true;
	char ch = '@';
	Board* pBoard = nullptr;
	void draw(char c) const 
	{
		gotoxy(x, y);
		std::cout << c;
	}
public:
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
	void jump();
	void fall();
	void keyPressed(char key);
	void move();
	bool getIsAlive() const { return isAlive; }
	void setBoard(Board& board) { pBoard = &board; }
};

