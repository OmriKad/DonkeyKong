#pragma once
#include "Character.h"
#include <cstdlib> // for rand()

class Ghost : public Character
{
    bool movingRight = true; // Default direction
    bool movingUp = false; // Default vertical direction
    int moveCounter = 0; // Counter to slow down movement
    int climbCounter = 0; // Counter to slow down climbing
    static constexpr int MOVE_DELAY = 1; // Delay factor to slow down movement
    static constexpr int CLIMB_DELAY = 5; // Delay factor to slow down climbing
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
        if (tileBelow != '=' && tileBelow != '<' && tileBelow != '>' && tileBelow != 'Q') {
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

        // Check if the ghost is on a ladder
        if (pBoard->is_ladder(x, y) || pBoard->is_ladder(x, y + 2)) {
            // Increment the climb counter
            climbCounter++;
            if (climbCounter < CLIMB_DELAY) {
                draw();
                return; // Skip climbing to slow down the ghost
            }
            climbCounter = 0; // Reset the counter

            // Randomly decide to move up or down the ladder
            if (rand() % 100 < 50) {
                movingUp = !movingUp;
            }

            // Calculate the next vertical position
            int nextY = movingUp ? y - 1 : y + 1;

            // Check if the next vertical position is valid
            if (pBoard->is_ladder(x, nextY)) {
                y = nextY; // Move up or down the ladder
            }
            else if (movingUp && !pBoard->is_pos_legal(x, nextY)) {
                y -= 2; // Move up to the next floor
            }
            else if (!movingUp && !pBoard->is_pos_legal(x, nextY) && pBoard->is_ladder(x, nextY + 1)) {
                y += 2; // Move down to the next floor
            }
        }
        draw();
    }
};
