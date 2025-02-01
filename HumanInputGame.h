#pragma once
#include "Game.h"
class HumanInputGame :
    public Game
{
public:
    HumanInputGame(bool saveMode = false) : Game(65, false, saveMode) {}
    void initGame(Board& currBoard, short currScore, short currLives, int levelIndex, bool fullGame) override;

};

