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
	char lives = 5;
	bool isAlive = true;
	bool canJump = true;
	bool canClimb = true;
	bool isJumping = false;
	bool isOnGround = true;
	bool isFalling = false;
	short jumpCount = 0;
	short const jumpLimit = 2;
	short fallCount = 0;
	short const fallLimit = 5;
	bool onLadder = false;
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
	void jump();
	void climbUp(bool isLastStep = false);
	void climbDown();
	void fall();
	void moveUp(bool isLastStep = false);
	void moveDown();
	void moveLeft();
	void moveRight();
	void keyPressed(char key);
	void move();
	bool getIsAlive() const { return isAlive; }
	void setBoard(Board& board) { pBoard = &board; }
};

