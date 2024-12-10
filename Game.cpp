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

	// Utility function for rand function
	srand(time(DEFAULT_VALUE));

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
	cout << "Press ESC to return to resume or (0) to return to the main menu," << endl;

	while (keyPressed != RETURN_TO_MENU && keyPressed != ESC)
		keyPressed = getKeyFromUser();

	return;
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
	Board board;
	Mario m;
	Barrel b;
	clearScreen();
	board.reset();
	board.print();
	m.setBoard(board);
	b.setBoard(board);
	while (true) {
		board.reset();
		char key = DEFAULT_VALUE;
		if (getKeyPress(key))
		{
			if (key == ESC)
				showPauseScreen(key);
			if (key == ESC)
			{
				clearScreen();
				board.print();
			}
			if (key == RETURN_TO_MENU)
				break;
		}
		m.keyPressed(key);
		Sleep(80);
		m.move();
		b.move();
	}
}