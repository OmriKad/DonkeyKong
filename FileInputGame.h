#pragma once
#include "Game.h"
class FileInputGame :
    public Game
{
public:
    FileInputGame(bool isSilent) : Game(isSilent ? 0 : 30, isSilent, false) {}
};

