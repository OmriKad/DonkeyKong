#include "Mario.h"

void Mario::keyPressed(char key) 
{
    key = std::tolower(key);
	switch (key)
	{
	case 'w':
		dir.y = -1;
		break;
    case 'x':
		dir.y = 1;
		break;
	case 'a':
		dir.x = -1;
		break;
	case 's':
		if (dir.x)
			dir.x = 0;
		if (dir.y)
			dir.y = 0;
		break;
	case 'd':
		dir.x = 1;
		break;
	default:
		break;
	}
}


// Responsible for the movement logic of mario accross the board.
void Mario::move()
{
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
			else
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
			Sleep(100);
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
			Sleep(100);
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
			Sleep(100);
		}
		else
		{
			if (isFalling)
			{
				if (fallCount > fallLimit)
					isAlive = false;
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




