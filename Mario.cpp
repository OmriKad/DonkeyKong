#include "Mario.h"

void Mario::keyPressed(char key) 
{
    key = std::tolower(key);

	switch (key)
	{
	case 'w':
        if (isOnGround)
        {
            isJumping = true;
            dir.y = -1;
			isOnGround = false;
        }
		break;
	case 'a':
		dir.x = -1;
		break;
	case 's':
        dir.x = 0;
		break;
	case 'd':
		dir.x = 1;
		break;
	default:
		break;
	}
}


void Mario::move()
{
    // Jumping logic
    if (isJumping)
    {
        dir.y = -1; // Move upwards
        jumpCount++;
        if (jumpCount >= 2)
        {
            isJumping = false;
            jumpCount = 0;
        }
    }
    // Falling logic
    else if (!pBoard->is_ground(x, y))
    {
        isFalling = true;
        dir.y = 1;  // Move downwards
    }
    else 
    {
		isOnGround = true;
        isFalling = false;
        dir.y = 0;  // Stop vertical movement
    }

    // Horizontal movement: Check for wall collisions
    int newX = x + dir.x;
    if (pBoard->is_pos_legal(newX, y))
        x = newX; // Update horizontal position
    else
        dir.x = 0; // Stop horizontal movement

    // Vertical movement: Apply dir.y
    int newY = y + dir.y;
    if (pBoard->is_pos_legal(x, newY))
        y = newY; // Update vertical position
    else
    {
        dir.y = 0;         // Stop vertical movement
        isJumping = false;  // Stop jumping if we hit something
        isFalling = false;  // Stop falling if we hit the ground
		isOnGround = true;  // We are on the ground
        jumpCount = 0;
    }
}



