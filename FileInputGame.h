#pragma once
#include "Game.h"
class FileInputGame :
    public Game
{
public:
    FileInputGame(bool isSilent) : Game(isSilent ? 0 : 30, isSilent, false) {}
	void game() override;
    void initGame(Board& currBoard, short currScore, short currLives, int levelIndex, bool fullGame) override;

};

