#include "HumanInputGame.h"
#include "Steps.h"
#include "Results.h"
#include <string>
#include <filesystem>
#define DEFAULT_VALUE 0


void HumanInputGame::initGame(Board& currBoard, short currScore, short currLives, int levelIndex, bool fullGame)
{
	long random_seed;
	Steps steps;
	Results results;
	std::string filename_prefix = levelsNames[levelIndex].substr(0, levelsNames[levelIndex].find_last_of('.'));
	std::string stepsFilename = filename_prefix + ".steps";
	std::string resultsFilename = filename_prefix + ".result";
	random_seed = static_cast<long>(std::chrono::system_clock::now().time_since_epoch().count());
	steps.setRandomSeed(random_seed);
	srand(random_seed);
	size_t iteration = 0;
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
			int marioCurrLife = m.getLives();
			pauseStatus(key, currBoard, isGameRunning, retFlag);
			if (retFlag == 2) break;

			m.keyPressed(key);       // Send key command to Mario
			steps.addStep(iteration, key);
			donkeyKong.update();    // Donkey Kong decides whether to throw a barrel
			checkGhostCollision(m, ghosts); // Check Mario's collision with ghosts
			moveBarrels(m);         // Move barrels
			moveGhosts(m);     // Move ghosts
			m.move();               // Mario moves according to input
			if (m.getLives() < marioCurrLife)
				results.addResult(iteration, Results::lostLife);
			checkAttacking(m);      // Check if Mario is attacking
			checkStatus(m, isGameRunning); // Check if Mario is dead or reached Pauline
			currBoard.printLegend(m.getLives(), m.getScore()); // Display the legend
			Sleep(sleepTime);
			++iteration;
		}
	}

	if (marioLost)
	{
		showDeathScreen();
	}
	else if (marioWon)
	{
		steps.saveSteps(stepsFilename);
		results.addResult(iteration, Results::finished);
		results.addResult(m.getScore(), Results::finalScore);
		results.saveResults(resultsFilename);
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

