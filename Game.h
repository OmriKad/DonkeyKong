#pragma once
#include "Mario.h"
#include "Board.h"

class Game
{
	char showMenu() const;
	void showInstructions() const;
	bool getKeyPress(char& keyPressed);
	void initGame();
	void showPauseScreen(char& keyPressed) const;
public:
	// This is the main method of the game,
	//from here we control the flow of the game with the help of the menu
	void game();
};