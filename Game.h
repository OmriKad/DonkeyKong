#pragma once
#include "Mario.h"
#include "Board.h"
#include "DonkeyKong.h"
#include "Barrel.h"
#include "Ghost.h"
#include <cstring>
#include <algorithm>
#include <vector>

class Game
{
protected:
	int sleepTime;
	bool silentMode;
	bool saveMode;
	void downloadLevels();
	// string vector for the file names
	std::vector<std::string> levelsNames;
	void scanFileNames(std::vector<std::string>& levelNames);
	char showMenu() const;
	void showInstructions() const;
	bool getKeyPress(char& keyPressed);
	void initGame(Board& currBoard, short currScore, short currLives, int levelIndex, bool fullGame);
	void moveGhosts(Mario& m);
	void pauseStatus(char& key, Board& board, bool& isGameRunning, int& retFlag);
	void showPauseScreen(char& keyPressed) const;
	void showNoLevelAviableScreen() const;
	void showDeathScreen() const;
	void showLevelCompletedScreen(short currScore, short currLives, int levelIndex, bool fullGame);
	void showLevelsScreen(char& keyPressed);
	void showWinScreen(short finalScore) const;
	bool marioLost = false;
	bool marioWon = false;
	DonkeyKong donkeyKong;
	std::vector<Barrel> barrels;
	std::vector<Ghost> ghosts;
	std::vector<Board> levels;
	void handleCollision(Mario& m);
	void checkGhostCollision(Mario& m, const std::vector<Ghost>& ghosts);
public:
	Game(int sleepTime = 50, bool silentMode = false, bool saveMode = false)
		: sleepTime(sleepTime), silentMode(silentMode), saveMode(saveMode) {
	}
	void setSaveMode(bool mode) { saveMode = mode; }
	bool getSaveMode() const { return saveMode; }
	void setSilentMode(bool mode) { silentMode = mode; }
	bool getSilentMode() const { return silentMode; }
	void setSleepTime(int time) { sleepTime = time; }
	void game();
	void checkStatus(Mario& m, bool& isGameRunning);
	void checkAttacking(Mario& m);
	void moveBarrels(Mario& m);
};