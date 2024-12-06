#pragma once

class Board
{
    static constexpr int MAX_X = 80;
    static constexpr int MAX_Y = 25;
    const char* originalBoard[MAX_Y] =
    {
        // 01234567890123456789012345678901234567890123456789012345678901234567890123456789
    "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ", // 0
    "Q                                                                              Q", // 1
    "Q                                                                              Q", // 2
    "Q                                                                              Q", // 3
    "Q                                                                              Q", // 4
    "Q                                                                              Q", // 5
    "Q                                                                              Q", // 6
    "Q                                                                              Q", // 7
    "Q                                                                              Q", // 8
    "Q                                                                              Q", // 9
    "Q                                                                              Q", // 10
    "Q                                                                              Q", // 11
    "Q                                                                              Q", // 12
    "Q                                                                              Q", // 13
    "Q                                                                              Q", // 14
    "Q                                               =========                      Q", // 15
    "Q                                                  H                           Q", // 16
    "Q                                                  H                           Q", // 17
    "Q                                                  H                           Q", // 18
    "Q                                                  H                           Q", // 19
    "Q                                                  H                           Q", // 20
    "Q                                              ========                        Q", // 21
    "Q                                                  H                           Q", // 22
    "Q                                                                              Q", // 23
    "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ"  // 24
    };
    char currentBoard[MAX_Y][MAX_X + 1]; // +1 for null terminator
public:
    void reset();
    void print() const;
    bool is_pos_legal(int x, int y) const
    {
        char tile = currentBoard[y][x];
        return tile != 'Q' && tile != '=' && tile != '>' && tile != '<';
    }
    bool is_ground(int x, int y) const { return currentBoard[y][x] != ' '; }
	bool is_ladder(int x, int y) const { return currentBoard[y][x] == 'H'; }
	char getChar(int x, int y) const { return currentBoard[y][x]; }
};