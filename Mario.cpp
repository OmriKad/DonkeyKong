#include "Mario.h"

void Mario::keyPressed(char key) 
{
    key = std::tolower(key);
	switch (key)
	{
	case 'w':
		if (!pBoard->is_ladder(x, y))
		{
			dir.y = -1;
			jump();
		}
		else
		{
			dir.y = -1;
			isClimbing = -1;
		}
		break;
    case 'x':
		if (pBoard->is_ladder(x, y + 2))
		{
			dir.y = 1;
			isClimbing = 1;
		}
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
	if (isClimbing == 1 && endOfLadder)
	{
		y += 1;
		endOfLadder = false;
	}
	else if (isClimbing == -1 && endOfLadder)
	{
		y -= 1;
		endOfLadder = false;
	}
	pBoard->is_pos_legal(x, y + dir.y, isClimbing, endOfLadder)? y += dir.y : dir.y = 0;
	pBoard->is_pos_legal(x + dir.x, y, isClimbing, endOfLadder) ? x += dir.x : dir.x = 0;
	draw();
	if (pBoard->is_air(x, y + 1)) { dir.y = 1;  fall(); }
}

void Mario::jump()
{
	for (int i = 0; (i < jumpLimit) && pBoard->is_air(x+dir.x, y-1); i++)
	{
		erase();
		pBoard->is_pos_legal(x + dir.x, y, isClimbing, endOfLadder) ? x += dir.x : dir.x = 0;
		y--;
		draw();
		Sleep(50);
	}
	dir.y = 0;
}

// Mario falls down the board, while each fall iteration fall count is incremented.
void Mario::fall()
{
	while (pBoard->is_air(x, y + dir.y))
	{
		erase();
		pBoard->is_pos_legal(x + dir.x, y, isClimbing, endOfLadder) ? x += dir.x : dir.x = 0;
		y++;
		draw();
		Sleep(150);
	}
	dir.y = 0;
}



