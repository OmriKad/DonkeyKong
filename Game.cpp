#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include "Board.h"
#include "utils.h"
#include "Mario.h"
#include "Barrel.h"
#include "Ghost.h"
#include "Game.h"
#include <regex>
#include <filesystem>
#define DEFAULT_VALUE 0
#define ESC 27
#define START_GAME '1'
#define LEVELS_SCREEN '2'
#define SHOW_INSTRUCTIONS '8'
#define EXIT_GAME '9'
#define RETURN_TO_MENU '0'
#define INITIAL_SCORE 100
#define MAX_LIVES 5

using namespace std;
void Game::game()
{
	downloadLevels();
	char keyPressed = DEFAULT_VALUE;

	// Disable cursor Method
	ShowConsoleCursor(false);

	while (keyPressed != EXIT_GAME)
	{
		// Show menu and get key input from the user
		keyPressed = showMenu();

		// Move the user to the next section according to his decision
		switch (keyPressed)
		{
			// Player pressed start game key
		case START_GAME:
			if (levels.empty())
				showNoLevelAviableScreen();
			else
				initGame(levels[0], INITIAL_SCORE, MAX_LIVES, 0, true);
			break;
			// Player pressed show instructions key
		case LEVELS_SCREEN:
			if (levels.empty())
				showNoLevelAviableScreen();
			else
				showLevelsScreen(keyPressed);
			break;
			// Player pressed show instructions key
		case SHOW_INSTRUCTIONS:
			showInstructions();
			break;
			// Player pressed exit game key
		case EXIT_GAME:
			clearScreen();
			return;
		default:
			break;
		}
	}
}

void Game::checkStatus(Mario& m, bool& isGameRunning)
{
	if (m.getLives() == 0)
	{
		m.setIsAlive(false);
		isGameRunning = false;
		marioLost = true;
	}
	else if (m.getHasWon())
	{
		m.setIsAlive(false);
		isGameRunning = false;
		marioWon = true;
	}
}

void Game::downloadLevels()
{
	// Get all the file names of the levels, for each name open the file, read the file content to the board and push the board to the levels vector
	scanFileNames(levelsNames);
	for (const auto& levelName : levelsNames) {
		Board board;
		board.readBoardFromFile(levelName);
		levels.push_back(board);
	}
}



void Game::scanFileNames(std::vector<std::string>& levelNames)
{
	// loop through the current directory and if the file name is of the format "dkong_*.txt" add it to the vector fileNames
	namespace fs = std::filesystem;
	for (const auto& entry : fs::directory_iterator(fs::current_path())) {
		auto filename = entry.path().filename();
		auto filenameStr = filename.string();
		if (filenameStr.substr(0, 6) == "dkong_" && filename.extension() == ".txt") {
			levelNames.push_back(filenameStr);
		}
	}
}

char Game::showMenu() const
{
	char keyPressed = DEFAULT_VALUE;

	clearScreen();
	std::cout << "***************" << std::endl;
	std::cout << "*             *" << std::endl;
	std::cout << "* DONKEY KONG *" << std::endl;
	std::cout << "*             *" << std::endl;
	std::cout << "***************" << std::endl;
	std::cout << "- A project by Omri and Yuval" << std::endl;
	Sleep(4000);
	clearScreen();

	// Present menu to user
	cout << "(1) Start a new game" << endl;
	cout << "(2) Choose a stage by name" << endl;
	cout << "(8) Read instructions" << endl;
	cout << "(9) EXIT" << endl;

	while (true)
	{
		if (_kbhit()) {
			keyPressed = getKeyFromUser();

			if (keyPressed == SHOW_INSTRUCTIONS || keyPressed == START_GAME || keyPressed == LEVELS_SCREEN || keyPressed == SHOW_INSTRUCTIONS || keyPressed == EXIT_GAME)
				break;
		}
	}

	return keyPressed;
}

void Game::showInstructions() const 
{
	char keyPressed = DEFAULT_VALUE;

	clearScreen();

	cout << "Donkey Kong Game Instructions" << endl << endl;

	cout << "Welcome to the game of Donkey Kong! This challenging classic game will test" << endl;
	cout << "your awareness and quick decision making skills. Below are the instructions" << endl;
	cout << "to help you understand and enjoy the game." << endl << endl;

	cout << "Game Objective:" << endl << endl;

	cout << "Princess Pauline '$' is in peril! She is held by the evil Donkey Kong '&' at the top of floor of the game board." << endl;
	cout << "You are playing as Mario '@' - a brave plumber who volunteered to save the princess." << endl;
	cout << "Climb your way up the floors using the ladders marked by 'H', or by jumping." << endl;
	cout <<	"Avoid getting hit by barrels 'O' that fall and roll according to their last slope '<' '>'. Barrles that fall from high ground will expoled '*'!" << endl;
	cout << "Ghosts 'x' exsist!, they would wander around floors in a random direction. Avoid getting hit my them as well!" << endl;
	cout << "Mario can Jump to avoid getting hit, but beware of falling from high ground!" << endl;
	cout << "Each stage has a hammer 'p' that can be used to destroy barrels and ghosts, When collecting it, mario would change to '%'." << endl;
	cout << "Once Mario reaches Pauline, you win the current level." << endl << endl;

	cout << "Controls:" << endl << endl;

	cout << "* Move Left: a or A" << endl;
	cout << "* Move Right: d or D" << endl;
	cout << "* Stay in place: s or S" << endl;
	cout << "* Jump or climb up: w or W" << endl;
	cout << "* Climb Down: x or X" << endl;
	cout << "* Use Hammer: p or P" << endl << endl;

	cout << "Health system:" << endl;
	cout << "Mario begins the level with 3 lives. For each hit or fall from height Mario losses 1 life and the level restarts." << endl;
	cout << "When reaching 0 lives, the game ends." << endl << endl;

	cout << "Score system:" << endl;
	cout << "Upon succssesful hammering down a barrel or a ghost, you recive 10 Pts. If a barrel or a ghost get you, you will lose 40 Pts." << endl;
	cout << "The points you recieve or lose will continue with you for the entire game, so try to gain as much as you can!" << endl;

	cout << "Have Fun and Good Luck!" << endl << endl;

	cout << "Press (0) to return to the main menu";

	while (keyPressed != RETURN_TO_MENU)
		keyPressed = getKeyFromUser();

	return;
}

void Game::showNoLevelAviableScreen() const {
	clearScreen();
	cout << endl << endl << endl;
	cout << "       No levels were found!       " << endl;
	cout << "       Please check files integrity.      " << endl;
	cout << "       Returning to main menu..." << endl;
	Sleep(4000);
}

void Game::showPauseScreen(char& keyPressed) const
{
	keyPressed = DEFAULT_VALUE;

	clearScreen();

	cout << "Game Paused" << endl << endl;
	cout << "Press ESC to return to resume or (0) to return to the main menu." << endl;

	while (keyPressed != RETURN_TO_MENU && keyPressed != ESC)
		keyPressed = getKeyFromUser();

	return;
}

void Game::showLevelsScreen(char& keyPressed)
{
	keyPressed = DEFAULT_VALUE;
	int i = 0;
	clearScreen();

	cout << "Donkey Kong level selection:" << endl << endl;
	for (const auto& it : levelsNames) {
		cout << "(" << (char)(i + 1 + '0') << ")" << it << endl;
		i++;
	}
	while (keyPressed != RETURN_TO_MENU)
	{
		keyPressed = getKeyFromUser();
		keyPressed -= '0';
		if (keyPressed > 0 || keyPressed < i) {
			Sleep(400);
			clearScreen();
			initGame(levels[keyPressed-1], INITIAL_SCORE, MAX_LIVES, keyPressed-1, false);
			return;
		}
	}
	return;
	
}

void Game::showDeathScreen() const
{
	clearScreen();

	cout << endl << endl << endl;
	cout << "       OH NO! MARIO DIED!       " << endl;
	cout << "       Returning to main menu..." << endl;
	Sleep(4000);
}

void Game::showLevelCompletedScreen(short currScore, short currLives, int newLevelIndex, bool fullGame) 
{
	clearScreen();
	cout << endl << endl << endl;
	cout << "       Level completed!       " << endl;
	cout << "       YOUR SCORE IS:" << currScore << endl;
	cout << "       Loading next level!       " << endl;
	Sleep(4000);
	initGame(levels[newLevelIndex], currScore, currLives, newLevelIndex, fullGame);
}

void Game::showWinScreen(short finalScore) const
{
	clearScreen();

	cout << endl << endl << endl;
	cout << "       PAULINE SAVED! YOU WON!       " << endl;
	cout << "       YOUR FINAL SCORE IS: " << finalScore << endl;
	cout << "       Returning to main menu..." << endl;
	Sleep(4000);
}

bool Game::getKeyPress(char& keyPressed) 
{
	if (_kbhit())
	{
		// Get key pressed
		keyPressed = _getch();

		// If player pressed escape, we shall pause the game.
		if (keyPressed == ESC)
			return true;
	}

	return false;
}



void Game::initGame(Board& currBoard, short currScore, short currLives, int levelIndex, bool fullGame) {
	bool isGameRunning = true; // Game stops when Mario loses all lives or wins
	Mario m;                   // Initialize Mario
	m.setScore(currScore);
	m.setLives(currLives);
	marioLost = false;         // Reset Mario's lost flag
	marioWon = false;          // Reset Mario's won flag

	while (isGameRunning) {
		// Clear the barrels and ghosts vectors from the previous session
		barrels.clear();
		ghosts.clear();
		// Intialize the mario
		m.setBoard(currBoard);
		m.resetPos();
		m.setIsAlive(true);
		// Initialize donkey kong
		donkeyKong.setBoard(currBoard);
		donkeyKong.setBarrels(barrels);
		donkeyKong.setDonkeyLoc(currBoard.getDonkeyStartX(), currBoard.getDonkeyStartY());
		// Initialize ghosts
		std::vector<Board::Position> ghostsPositions = currBoard.getGhostsStartPos();
		for (auto& pos : ghostsPositions) {
            Ghost g(pos.x, pos.y);
			g.setBoard(currBoard);
			ghosts.push_back(g);
		}
		clearScreen();
		currBoard.reset(); // Reset and display the board
		currBoard.print();


		while (m.getIsAlive()) { // Loop for Mario's current life
			char key = DEFAULT_VALUE;
			int retFlag;
			pauseStatus(key, currBoard, isGameRunning, retFlag);
			if (retFlag == 2) break;

			m.keyPressed(key);       // Send key command to Mario
			donkeyKong.update();    // Donkey Kong decides whether to throw a barrel
			moveBarrels(m);         // Move barrels
			moveGhosts(m);     // Move ghosts
			m.move();               // Mario moves according to input
			checkAttacking(m);      // Check if Mario is attacking
			checkCollision(m);      // Check if Mario got hit
			checkGhostCollision(m, ghosts); // Check Mario's collision with ghosts
			checkStatus(m, isGameRunning); // Check if Mario is dead or reached Pauline
			currBoard.printLegend(m.getLives(), m.getScore()); // Display the legend
			Sleep(90);
		}
	}

	if (marioLost)
	{
		showDeathScreen();
	}
	else if (marioWon)
	{
		if (&currBoard == &levels.back() || fullGame == false) // Check if it's the final level
		{
			showWinScreen(m.getScore());
		}
		else
		{
			showLevelCompletedScreen(m.getScore(), m.getLives(), levelIndex + 1, true);
		}
	}
	else
	{
		return; // Return to main menu
	}
}

void Game::moveGhosts(Mario& m) {
	for (auto it = ghosts.begin(); it != ghosts.end(); )
	{
		it->move();
		it++;
	}
}

void Game::pauseStatus(char& key, Board& board, bool& isGameRunning, int& retFlag)
{
	if (getKeyPress(key))
	{
		showPauseScreen(key);
		if (key == ESC)
		{
			clearScreen();
			board.print();
		}
		else
		{
			isGameRunning = false;
			retFlag = 2;
		}
	}
}

void Game::checkGhostCollision(Mario& m, const std::vector<Ghost>& ghosts) {
	for (const auto& ghost : ghosts) {
		if (m.getX() == ghost.getX() && m.getY() == ghost.getY()) {
			m.decreaseLife();
			m.decreasePoints();
			m.setIsAlive(false);
			break;
		}
	}
}



void Game::checkCollision(Mario& m)
{
	const int EXPLODING_BARREL_DISTANCE = 2;
	const int NON_EXPLODING_BARREL_DISTANCE = 0;

	for (const auto& barrel : barrels)
	{
		int dx = abs(m.getX() - barrel.getX());
		int dy = abs(m.getY() - barrel.getY());

		if (barrel.getExploded() && dx <= EXPLODING_BARREL_DISTANCE && dy <= EXPLODING_BARREL_DISTANCE)
		{
			handleCollision(m);
			return;
		}
		else if (!barrel.getExploded() && dx == NON_EXPLODING_BARREL_DISTANCE && m.getY() == barrel.getY())
		{
			handleCollision(m);
			return;
		}
	}
}

void Game::checkAttacking(Mario& m)
{
	if (m.getUsingHammer())
	{
		for (auto barrel = barrels.begin(); barrel != barrels.end();)
		{
			int dx = abs(m.getX() - barrel->getX());
			if (dx <= 2 && m.getY() == barrel->getY())
			{
				barrel->erase();
				barrel = barrels.erase(barrel);
				m.gainPoints();
			}
			else
			{
				++barrel;
			}
		}
		for (auto ghost = ghosts.begin(); ghost != ghosts.end();)
		{
			int dx = abs(m.getX() - ghost->getX());
			if (dx <= 2 && m.getY() == ghost->getY())
			{
				ghost->erase();
				ghost = ghosts.erase(ghost);
				m.gainPoints();
			}
			else
			{
				++ghost;
			}
		}
		m.setUsingHammer(false);
	}
}

void Game::handleCollision(Mario& m)
{
	m.decreaseLife();
	m.decreasePoints();
	m.setIsAlive(false);
}


// Responsible for moving all the barrles on the board and to check for collisions
void Game::moveBarrels(Mario& m)
{
	for (auto it = barrels.begin(); it != barrels.end(); )
	{
		it->move();

		// Remove barrel if it has exploded
		if (it->getExploded())
		{
			it = barrels.erase(it);
		}
		else
		{
			++it;
		}
	}
}
