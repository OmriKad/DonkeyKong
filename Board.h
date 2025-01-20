#pragma once
#include <vector>
#include <string>
class Board
{
public:
    struct Position { int x, y; };
private:
    bool boardIsLegal;
    static constexpr int MAX_X = 80;
    static constexpr int MAX_Y = 25;
    Position marioStartPos;
    Position donkeyStartPos;
    Position legendStartPos;
    std::vector<Position> ghostsStartPos;

    char originalBoard[MAX_Y][MAX_X + 1];
    char currentBoard[MAX_Y][MAX_X + 1]; // +1 for null terminator
public:
    void reset();
    void print() const;
    bool is_pos_legal(int x, int y) const
    {
        char tile = currentBoard[y][x];
        return tile != 'Q' && tile != '=' && tile != '>' && tile != '<';
    }
    void setCharAt(int x, int y, char c)
    {
        currentBoard[y][x] = c;
    }
    bool is_air(int x, int y) const { return currentBoard[y][x] == ' '; }
    bool is_ladder(int x, int y) const { return currentBoard[y][x] == 'H'; }
    bool is_pauline(int x, int y) const { return currentBoard[y][x] == '$'; }
    bool is_barrel(int x, int y) const { return currentBoard[y][x] == 'O'; }
    bool is_ghost(int x, int y) const { return currentBoard[y][x] == 'x'; }
    bool is_hammer(int x, int y) const { return currentBoard[y][x] == 'p'; }
    char getChar(int x, int y) const { return currentBoard[y][x]; }
    void printLegend(short lives, short score) const;
    void setBoardIsLegal(bool b) { boardIsLegal = b; }
    void readBoardFromFile(const std::string& fileName, bool& rejected);
    void fillQandSpaces(std::string& line, int y);
    bool getBoardIsLegal() const { return boardIsLegal; }
    int getMarioStartX() const { return marioStartPos.x; }
    int getMarioStartY() const { return marioStartPos.y; }
    int getDonkeyStartX() const { return donkeyStartPos.x; }
    int getDonkeyStartY() const { return donkeyStartPos.y; }
    int getLegendStartX() const { return legendStartPos.x; }
    int getLegendStartY() const { return legendStartPos.y; }
    std::vector<Position> getGhostsStartPos() const { return ghostsStartPos; }
};