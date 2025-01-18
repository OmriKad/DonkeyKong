#pragma once

#include <iostream>
#include <windows.h>
#include "utils.h"
#include "Board.h"
#include "Character.h"

class Mario : public Character
{
	// Some of the class attributes and the movement + board logic was inspired by the code example published my Amir Kirsh.
	int lastDirX = 0;
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
	bool hasHammer = false;
	bool usingHammer = false;
public:
	Mario() : Character() { ch = '@'; underChar = ' '; isAlive = true; hasWon = false; }

	void decreaseLife() { lives--; }


	void keyPressed(char key);
	void move();
	void resetPos() { x = 65; y = 23; ch = '@'; hasHammer = false; }
	bool getIsAlive() const { return isAlive; }
	void setIsAlive(bool b) { isAlive = b; }
	bool getHasWon() const { return hasWon; }
	void setHasWon(bool b) { hasWon = b; }
	short getLives() const { return lives; }
	bool getHasHammer() const { return hasHammer; }
	bool getUsingHammer() const { return usingHammer; }
	void setUsingHammer(bool b) { usingHammer = b; }
};