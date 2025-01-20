#pragma once
#include "Character.h"
#include <cstdlib> // for rand()

class Ghost : public Character
{
    bool movingRight = true; // Default direction
    int moveCounter = 0; // Counter to slow down movement
    static constexpr int MOVE_DELAY = 1; // Delay factor to slow down movement
public:
    Ghost(int startX, int startY) {
        ch = 'x';
        x = startX;
        y = startY;
        underChar = ' ';
    }

    void move() {
        erase();

        // Increment the move counter
        moveCounter++;
        if (moveCounter < MOVE_DELAY) {
            draw();
            return; // Skip movement to slow down the ghost
        }
        moveCounter = 0; // Reset the counter

        // Check the tile below the ghost to ensure it's a floor
        char tileBelow = pBoard->getChar(x, y + 1);
        if (tileBelow != '=' && tileBelow != '<' && tileBelow != '>') {
            // Ghost is not on a floor, reverse direction
            movingRight = !movingRight;
        }

        // Change direction probabilistically
        if (rand() % 100 < 5) {
            movingRight = !movingRight;
        }

        // Calculate the next position
        int nextX = movingRight ? x + 1 : x - 1;

        // Check if the next position is valid
        if (!pBoard->is_pos_legal(nextX, y) || pBoard->getChar(nextX, y + 1) == ' ' || pBoard->getChar(nextX, y) == 'x') {
            movingRight = !movingRight; // Reverse direction at the edge of a floor
        }
        else {
            x = nextX; // Move to the next position
        }

        draw();
    }

};