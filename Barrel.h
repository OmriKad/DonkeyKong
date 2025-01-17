#pragma once
#include "Character.h"
#include <iostream>
#include "utils.h"
#include <windows.h>

class Barrel : public Character
{
    int lastDirX = 0;
    bool needToExploade = false;
    bool exploded = false;
    short fallCount = 0;
    static const short fallLimit = 8;
    int fallDelayCounter = 0;
    int fallDelay = 2;

public:
    Barrel() { ch = 'O'; x = 18; y = 3; }



    void move();
    bool getNeedToExploade() const { return needToExploade; }
    void setNeedToExploade(bool value) { needToExploade = value; }
    void setDir(int x, int y) { dir.x = x; dir.y = y; }
    void addFallCount() { fallCount++; }
    void resetFallCount() { fallCount = 0; }
    short getFallCount() const { return fallCount; }
    short getFallLimit() const { return fallLimit; }
    void updateXY() { x += dir.x; y += dir.y; }
    void explode() { setExploded(true); ch = '*'; draw(); Sleep(100); erase(); }
    void setLastDirX(int value) { lastDirX = value; }
    int getLastDirX() const { return lastDirX; }
    void setExploded(bool value) { exploded = value; }
    bool getExploded() const { return exploded; }
};