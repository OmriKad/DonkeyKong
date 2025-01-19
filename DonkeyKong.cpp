#include "DonkeyKong.h"
#include "utils.h"
void DonkeyKong::draw() const
{
	gotoxy(x, y);
	std::cout << ch;
}

void DonkeyKong::erase() const
{
	gotoxy(x, y);
	std::cout << ' ';
}

void DonkeyKong::throwBarrel()
{
    if (pBarrels && pBoard)
    {
        Barrel newBarrel;
        newBarrel.setPosition(x, y);
        newBarrel.setBoard(*pBoard);
        pBarrels->push_back(newBarrel);
    }
}

void DonkeyKong::update()
{
    // Randomly decide to throw a barrel
    if (rand() % 100 < 2) // 2% chance each update
    {
        throwBarrel();
    }
    draw();
}