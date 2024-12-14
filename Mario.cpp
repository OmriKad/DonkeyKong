#include "Mario.h"

void Mario::keyPressed(char key) 
{
    key = std::tolower(key);
    // Check if Mario is on the ground
    bool isOnGround = !pBoard->is_air(x, y + 1);
    // Check if Mario is on a ladder
    bool isOnLadder = pBoard->is_ladder(x, y);
	// Check if there is a ladder beneath the floor
	bool ladderBelow = pBoard->is_ladder(x, y + 2);

    switch (key)
    {
    case 'w':
        if (isOnLadder)
        {
            dir.y = -1; // Climb up
        }
        else if (isOnGround)
        {
            dir.y = -1; // Jump
        }
        break;
    case 'x':
        if (ladderBelow)
        {
            dir.y = 1; // Climb down
        }
        break;
    case 'a':
        dir.x = -1; // Move left
        break;
    case 's':
        dir.x = 0;  // Stop horizontal movement
        dir.y = 0;  // Stop vertical movement
        break;
    case 'd':
        dir.x = 1;  // Move right
        break;
    default:
        break;
    }
}


// Responsible for the movement logic of mario accross the board.
void Mario::move()
{
	if (pBoard->is_pauline(x, y))
		hasWon = true;
	/*if (pBoard->is_barrel(x, y))
	{
		lives--;
		isAlive = false;
		return;
	}*/
	erase();
	// Responisble for the lateral movement of mario on the board.
	switch (dir.x)
	{
	case 1:
		pBoard->is_pos_legal(x + dir.x, y) ? x++ : dir.x = 0;
		break;
	case -1:
		pBoard->is_pos_legal(x + dir.x, y) ? x-- : dir.x = 0;
		break;
		
	}

	// Responsible for the vertical movement of mario on the board.
	switch (dir.y)
	{
	case 0:
		if (pBoard->is_air(x, y + 1))
			dir.y = 1;
		break;
	case -1: // User wanted to go up.
		if (pBoard->is_air(x, y - 1))
		{
			if (jumpCount == jumpLimit)
			{
				dir.y = 0;
				jumpCount = 0;
			}
			else if (jumpCount < jumpLimit)
			{	
				y--;
				jumpCount++;	
			}
		}
		else if (pBoard->is_ladder(x, y - 1))
		{
			if (pBoard->is_ladder(x, y - 2))
				y--;
			else
			{
				y--;
				dir.y = 0;
			}
		}
		else
		{
			if (pBoard->is_ladder(x, y))
			{
				y -= 2;
				dir.y = 0;
			}
			else
			{
				jumpCount = 0;
				dir.y = 0;
			}
		}
		break;

	case 1: // User wanted to go down.
		if (pBoard->is_air(x, y + 1))
		{
			y++;
			fallCount++;
			isFalling = true;
		}
		else if (pBoard->is_ladder(x, y + 1))
		{
			if (pBoard->is_ladder(x, y + 2))
				y++;
			else
			{
				y++;
				dir.y = 0;
			}		
		}
		else
		{
			if (isFalling)
			{
				if (fallCount > fallLimit)
				{
					lives--;
					isAlive = false;
					fallCount = 0;
				}
				else
				{
					fallCount = 0;
					dir.y = 0;
					isFalling = false;
				}
			}
			else
			{
				if (pBoard->is_ladder(x, y + 2))
					y++;
				else
					dir.y = 0;
			}
		}
	}
	draw();
}




