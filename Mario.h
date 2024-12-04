#pragma once

#include <iostream>

#include "utils.h"
#include "Board.h"

class Mario {
	static constexpr char keys[] = { 'w', 'a', 'x', 'd', 's'};
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);
	struct Direction { int x, y; }; // inner private struct
	int x = 23, y = 23;
	Direction dir{0, 0}; // current direction: dir.x, dir.y
	bool isJumping = false;
	bool isOnGround = true;
	bool isFalling = false;
	short jumpCount = 0;
	bool isClimbing = false;
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
		draw(' ');
	}
	void keyPressed(char key);
	void move();
	void setBoard(Board& board)
	{
		pBoard = &board;
	}
};

