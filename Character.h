#pragma once
#include "utils.h"
#include <iostream>
#include "Board.h"

class Character
{
protected:
    int x = 0, y = 0;
    struct Direction { int x, y; }; // inner private struct
    Direction dir{ 0, 0 }; // current direction: dir.x, dir.y
    char ch = ' ';
    char underChar;
    Board* pBoard = nullptr;

    void draw(char c) const
    {
        gotoxy(x, y);
        std::cout << c;
    }

public:
    int getX() const { return x; }
    int getY() const { return y; }
    void setPosition(int posX, int posY) { x = posX; y = posY; }
    void setBoard(Board& board) { pBoard = &board; }
    void updateBoardPosition(char c)
    {
        pBoard->setCharAt(x, y, c);
    }
    void draw()
    {
        underChar = pBoard->getChar(x, y);
        underChar = isCharacter(underChar) ? ' ' : underChar;
        updateBoardPosition(ch);
        draw(ch);
    }
    bool isCharacter(char ch)
    {
        return (ch == 'O' || ch == '@' || ch == 'x');
    }
    void erase()
    {
        updateBoardPosition(underChar);
        draw(underChar);
    }
};
