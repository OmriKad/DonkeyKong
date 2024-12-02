#include "Mario.h"

void Mario::keyPressed(char key) 
{
    key = std::tolower(key);
    if (key == 'a') 
    {
        dir.x = -1;  // Move left continuously
    }
    else if (key == 'd')
    {
        dir.x = 1;   // Move right continuously
    }
    else if (key == 'w' && !isJumping && !isFalling) 
    {
        isJumping = true;
        jumpCount = 0;
        dir.y = -1;  // Start jumping upwards
    }
    else if (key == 's')
    {
        dir.x = 0;
    }
}


void Mario::move() {
    // Update positions
    int newX = x + dir.x;
    int newY = y + dir.y;

    // Horizontal movement: Check for wall collisions
    if (!pBoard->is_pos_legal(newX, y)) 
    {
        dir.x = 0;   // Stop horizontal movement
        newX = x;    // Reset to previous x position
    }

    // Jumping logic
    if (isJumping)
    {
        jumpCount++;
        if (jumpCount >= 2)
        {
            isJumping = false;
            isFalling = true;
            jumpCount = 0;
            dir.y = 1;   // Start falling downwards
        }
        else
        {
            dir.y = -1;  // Continue moving upwards
        }
    }

    // Falling logic
    if (!isJumping && !pBoard->is_ground(newX, newY))
    {
        isFalling = true;
        dir.y = 1;       // Move downwards
    }
    else if (pBoard->is_ground(newX, newY)) 
    {
        isFalling = false;
        dir.y = 0;       // Stop vertical movement
        newY = y;        // Align with the ground
    }

    // Vertical movement: Check for collisions
    if (!pBoard->is_pos_legal(newX, newY))
    {
        dir.y = 0;   // Stop vertical movement
        newY = y;    // Reset to previous y position
    }

    // Update Mario's position
    x = newX;
    y = newY;
}

