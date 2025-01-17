#include <iostream>
#include <windows.h>
#include <conio.h>

#include "Board.h"
#include "utils.h"
#include "Mario.h"
#include "Barrel.h"
#include "Game.h"

#define DEFAULT_VALUE 0
#define ESC 27
#define START_GAME '1'
#define SHOW_INSTRUCTIONS '8'
#define EXIT_GAME '9'
#define RETURN_TO_MENU '0'


using namespace std;

void Game::game()
{
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
			initGame();
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
	cout << "(8) Read instructions" << endl;
	cout << "(9) EXIT" << endl;

	while (true)
	{
		if (_kbhit()) {
			keyPressed = getKeyFromUser();

			if (keyPressed == SHOW_INSTRUCTIONS || keyPressed == START_GAME || keyPressed == SHOW_INSTRUCTIONS || keyPressed == EXIT_GAME)
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

	cout << "Pauline '$' is in peril! She is held by the evil Donkey Kong '&' at the top of floor of the game board." << endl;
	cout << "You are playing as Mario '@' - a brave plumber that needs to save the princess." << endl;
	cout << "Climb your way up the floors using the ladders marked by 'H'." << endl;
	cout <<	"avoid getting hit by barrels 'O' that fall and roll according to their last slope '<' '>'. Barrles that fall from high ground will expoled '*'!" << endl;
	cout << "Mario can Jump to avoid getting hit, but beware of falling from high ground!" << endl;
	cout << "Once Mario reaches Pauline, you win the current level." << endl << endl;

	cout << "Controls:" << endl << endl;

	cout << "* Move Left: a or A" << endl;
	cout << "* Move Right: d or D" << endl;
	cout << "* Stay in place: s or S" << endl;
	cout << "* Jump or climb up: w or W" << endl;
	cout << "* Climb Down: x or X" << endl << endl;

	cout << "Health system:" << endl;
	cout << "Mario begins the level with 3 lives. For each hit or fall from height Mario losses 1 life and the level restarts." << endl;
	cout << "When reaching 0 lives, the game ends." << endl << endl;

	cout << "Have Fun and Good Luck!" << endl << endl;

	cout << "Press (0) to return to the main menu";

	while (keyPressed != RETURN_TO_MENU)
		keyPressed = getKeyFromUser();

	return;
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

void Game::showDeathScreen() const
{
	clearScreen();

	cout << endl << endl << endl;
	cout << "       OH NO! MARIO DIED!       " << endl;
	cout << "       Returning to main menu..." << endl;
	Sleep(4000);
}

void Game::showWinScreen() const
{
	clearScreen();

	cout << endl << endl << endl;
	cout << "       PAULINE SAVED! YOU WON!       " << endl;
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

void Game::initGame()
{
	bool isGameRunning = true; // game is stopped when lost all lives or reached pauline
	Mario m; // initialize mario
	marioLost = false; // reset marioLost flag
	marioWon = false; // reset marioWon flag
	while (isGameRunning)
	{
		barrels.clear();
		Board board; // initialize board
		m.resetPos();
		m.setIsAlive(true);
		clearScreen();
		board.reset(); // reseting and displating the board
		board.print();
		m.setBoard(board);
		donkeyKong.setBoard(board); // inititalizing donkey kong and his barrels
		donkeyKong.setBarrels(barrels);
		while (m.getIsAlive()) // the loop of mario current life
		{
			char key = DEFAULT_VALUE;
			int retFlag;
			pauseStatus(key, board, isGameRunning, retFlag);
			if (retFlag == 2) break;
			m.keyPressed(key); // sending the key command to mario to figure out direction
			donkeyKong.update(); // donkey kong decideds weather to throw another barrel or not
			moveBarrels(m);
			m.move(); // mario moving according to the input
			checkCollision(m); // checking if mario got hit
			checkStatus(m, isGameRunning); // checking the general game status - if mario is dead and lost or reached pauline and won
			board.printLives(m.getLives()); // printing to the user the current no. of lives
			Sleep(90);
		}
	}
	if (marioLost)
		showDeathScreen();
	else if (marioWon)
		showWinScreen();
}

void Game::pauseStatus(char& key, Board& board, bool& isGameRunning, int& retFlag)
{
	retFlag = 1;
	if (getKeyPress(key))
	{
		if (key == ESC) // user want to pause
			showPauseScreen(key);
		if (key == ESC) // user unpaused
		{
			clearScreen();
			board.print();
		}
		if (key == RETURN_TO_MENU) // user wanted to end current game and return to main menu
		{
			isGameRunning = false;
			{ retFlag = 2; return; };
		}
	}
}

void Game::checkCollision(Mario& m)
{
	const int EXPLODING_BARREL_DISTANCE = 2;
	const int NON_EXPLODING_BARREL_DISTANCE = 1;

	for (const auto& barrel : barrels)
	{
		int dx = abs(m.getX() - barrel.getX());
		int dy = abs(m.getY() - barrel.getY());

		if (barrel.getExploded() && dx <= EXPLODING_BARREL_DISTANCE && dy <= EXPLODING_BARREL_DISTANCE)
		{
			handleCollision(m);
			return;
		}
		else if (!barrel.getExploded() && dx <= NON_EXPLODING_BARREL_DISTANCE && m.getY() == barrel.getY())
		{
			handleCollision(m);
			return;
		}
	}
}

void Game::handleCollision(Mario& m)
{
	m.decreaseLife();
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
			checkCollision(m);
			it = barrels.erase(it);
		}
		else
		{
			++it;
		}
	}
}
