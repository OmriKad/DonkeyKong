#include "FileInputGame.h"
#include "Results.h"
#include "Steps.h"
#include "utils.h"
#define INITIAL_SCORE 0
#define MAX_LIVES 5
void FileInputGame::game()
{
	downloadLevels();
	ShowConsoleCursor(false);
	if (levels.empty())
	{
		showNoLevelAviableScreen();
		return;
	}
	initGame(levels[0], INITIAL_SCORE, MAX_LIVES, 0, true);
}
void FileInputGame::initGame(Board& currBoard, short currScore, short currLives, int levelIndex, bool fullGame)
{
	currBoard.setIsSilent(silentMode);
	size_t nextLostLifeIteration = -1;
	long random_seed;
	Steps steps;
	Results results;
	std::string filename_prefix = levelsNames[levelIndex].substr(0, levelsNames[levelIndex].find_last_of('.'));
	std::string stepsFilename = filename_prefix + ".steps";
	std::string resultsFilename = filename_prefix + ".result";
	steps = Steps::loadSteps(stepsFilename);
	if (steps.steps.size() == 0)
	{
		clearScreen();
		std::cerr << "Error: Could not read file " << stepsFilename << ", file corrupted or missing." << std::endl;
		Sleep(4000);
		clearScreen();
		return;
	}
	random_seed = steps.getRandomSeed();
	results = Results::loadResults(resultsFilename);
	srand(random_seed);
	bool isGameRunning = true; // Game stops when Mario loses all lives or wins
	Mario m;                   // Initialize Mario
	m.setScore(currScore);
	m.setLives(currLives);
	marioLost = false;         // Reset Mario's lost flag
	marioWon = false;          // Reset Mario's won flag
	size_t iteration = 0;
	while (isGameRunning) {
		if (results.isFinishedBy(iteration)) {
			reportResultError("Results file reached finish while game hadn't!", filename_prefix, iteration);
			break;
		}
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
			if (steps.isNextStepOnIteration(iteration)) {
				m.keyPressed(steps.popStep());
			}
			int marioCurrLife = m.getLives();
			donkeyKong.update();    // Donkey Kong decides whether to throw a barrel
			checkGhostCollision(m, ghosts); // Check Mario's collision with ghosts
			moveBarrels(m);         // Move barrels
			moveGhosts(m);     // Move ghosts
			m.move();               // Mario moves according to input
			if (m.getLives() < marioCurrLife)
			{
				if (results.popResult() != std::pair{ iteration, Results::lostLife }) {
					reportResultError("Results file doesn't match lost life event!", filename_prefix, iteration);
					isGameRunning = false;
					break;
				}
				nextLostLifeIteration = results.getNextLostLife();
			}
			checkAttacking(m);      // Check if Mario is attacking
			checkStatus(m, isGameRunning); // Check if Mario is dead or reached Pauline
			currBoard.printLegend(m.getLives(), m.getScore()); // Display the legend
			Sleep(sleepTime);
			++iteration;
		}
	}

	if (marioLost)
	{
		clearScreen();
		return;
	}
	else if (marioWon)
	{
		if (&currBoard == &levels.back() || fullGame == false) // Check if it's the final level
		{
			clearScreen();
			std::cout << "Load was ok, no errors." << std::endl;
			return;
		}
		else
			initGame(levels[levelIndex + 1], m.getScore(), m.getLives(), levelIndex + 1, true);
	}
	else
	{
		return; // Return to main menu
	}
}
