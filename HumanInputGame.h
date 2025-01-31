#pragma once
#include "Game.h"
class HumanInputGame :
    public Game
{
public:
    HumanInputGame(bool saveMode = false) : Game(65, false, saveMode) {}
};

