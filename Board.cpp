#include <cstring>
#include <iostream>
#include <fstream>
#include "utils.h"
#include "Board.h"
#include "Ghost.h"
#include "Barrel.h"
#include <string>

void Board::reset() {
	for (int i = 0; i < MAX_Y; i++) {
		memcpy(currentBoard[i], originalBoard[i], MAX_X + 1);
	}
}

void Board::print() const {
	for (int i = 0; i < MAX_Y - 1; i++) {
		std::cout << currentBoard[i] << '\n';
	}
	std::cout << currentBoard[MAX_Y - 1];
}


void Board::printLegend(short lives, short score) const
{
	gotoxy(legendStartPos.x, legendStartPos.y);
    std::cout << "Lives: " << lives << std::endl;
	gotoxy(legendStartPos.x, legendStartPos.y + 1);
	std::cout << "Score: " << score << std::endl;
}


void Board::readBoardFromFile(const std::string& fileName, bool& rejected)
{
	// The function open a file and read the content char by char to the originalBoard array while updating the start positions.
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		std::cerr << "Error: Could not open file " << fileName << std::endl;
		return;
	}
	std::string line;
	int y = 0;
	int marioCount = 0;
	int donkeyCount = 0;
	int paulineCount = 0;
	int legendCount = 0;
	while (std::getline(file, line) && y < MAX_Y)
	{
		fillQandSpaces(line, y);
		for (int x = 0; x < MAX_X; x++)
		{
			char ch = line[x];
			switch (ch)
			{
			case '@':
				marioCount++;
				marioStartPos = { x, y };
				originalBoard[y][x] = ' ';
				break;
			case 'L':
				legendCount++;
				legendStartPos = { x, y };
				originalBoard[y][x] = ' ';
				break;
			case '&':
				donkeyCount++;
				donkeyStartPos = { x, y };
				originalBoard[y][x] = ' ';
				break;
			case 'x':
				ghostsStartPos.push_back({ x, y });
				originalBoard[y][x] = ' ';
				break;
			case '$':
				paulineCount++;
				originalBoard[y][x] = ch;
				break;
			default:
				originalBoard[y][x] = ch;
				break;
			}
		}
		y++;
	}
	if (marioCount != 1 || donkeyCount != 1 || paulineCount != 1 || legendCount != 1)
	{
		rejected = true;
	}
	file.close();
}

void Board::fillQandSpaces(std::string& line, int y)
{
	// Responisble for making sure the floor and cieling are filled with Q.
	if (y == 0 || y == MAX_Y - 1)
		line = std::string(MAX_X - 1, 'Q');
	// Responisble for making sure the sides walls are filled with Q.
	else
	{
		if (line.size() > MAX_X - 1)
		{
			line = line.substr(0, MAX_X - 1);
			line[0] = line[MAX_X - 2] = 'Q';
		}
		else if (line.size() < MAX_X - 1)
		{
			line += std::string(MAX_X - 1 - line.size(), ' ');
			line[0] = line[MAX_X - 2] = 'Q';
		}
	}
}
