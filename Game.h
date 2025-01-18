#pragma once
#include "Mario.h"
#include "Board.h"
#include "DonkeyKong.h"
#include "Barrel.h"
#include "Ghost.h"
#include <vector>

class Game
{
	char showMenu() const;
	void showInstructions() const;
	bool getKeyPress(char& keyPressed);
	void initGame();
	void moveGhosts(std::vector<Ghost>& ghosts);
	void pauseStatus(char& key, Board& board, bool& isGameRunning, int& retFlag);
	void showPauseScreen(char& keyPressed) const;
	void showDeathScreen() const;
	void showWinScreen() const;
	bool marioLost = false;
	bool marioWon = false;
	DonkeyKong donkeyKong;
	std::vector<Barrel> barrels;
	void handleCollision(Mario& m);
	void checkGhostCollision(Mario& m, const std::vector<Ghost>& ghosts); // Add this line
public:
	// This is the main method of the game,
	//from here we control the flow of the game with the help of the menu
	void game();
	void checkStatus(Mario& m, bool& isGameRunning);
	void checkCollision(Mario& m);
	void moveBarrels(Mario& m);
};