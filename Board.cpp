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


void Board::readBoardFromFile(const std::string& fileName)
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
	while (std::getline(file, line) && y < MAX_Y)
	{
		for (int x = 0; x < MAX_X; x++)
		{
			char ch = line[x];
			switch (ch)
			{
			case '@':
				marioStartPos = { x, y };
				originalBoard[y][x] = ' ';
				break;
			case 'L':
				legendStartPos = { x, y };
				originalBoard[y][x] = ' ';
				break;
			case '&':
				donkeyStartPos = { x, y };
				originalBoard[y][x] = ' ';
				break;
			case 'x':
				ghostsStartPos.push_back({ x, y });
				originalBoard[y][x] = ' ';
				break;
			default:
				originalBoard[y][x] = ch;
				break;
			}
		}
		y++;
	}
	file.close();
}

