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

void Mario::moveLeft()
{
	if (pBoard->is_pos_legal(x - 1, y))
	{
		erase();
		x--;
		draw();
	}
    else
	    dir.x = 0;
}

void Mario::moveRight()
{
	if (pBoard->is_pos_legal(x + 1, y))
	{
		erase();
		x++;
		draw();
	}
    else
        dir.x = 0;
}

void Mario::moveUp(bool isLastStep)
{
	if (pBoard->is_pos_legal(x, y - 1))
	{
		erase();
		y--;
		draw();
	}
	else if (isLastStep)
	{
		erase();
		y--;
		y--;
		draw();
	}
    else
	    dir.y = 0;
}

void Mario::moveDown()
{
	if (pBoard->is_pos_legal(x, y + 1))
	{
		erase();
		y++;
		draw();
	}
    else
        dir.y = 0;
}

// Responsible for the movement logic of mario accross the board.
void Mario::move()
{
	isOnGround = pBoard->is_ground(x, y + 1);
	char tile = pBoard->getChar(x + dir.x, y + dir.y);
	canJump = (tile == ' ') && (isOnGround || isJumping);
	canClimb = (tile == 'H' || tile == '=') && (isOnGround || onLadder);
	if (!isOnGround && !isJumping && !isClimbing)
	{
		isFalling = true;
		dir.y = 1;
	}
	if (dir.x == -1)
	{
		moveLeft();
	}
	if (dir.x == 1)
	{
		moveRight();
	}
	if (dir.y == -1)
	{
		if (canJump)
		{
			jump();
		}
		if (canClimb)
		{
			bool isLastStep = false;
			if (pBoard->getChar(x + dir.x, y + dir.y == '='))
				isLastStep = true;

			climbUp(isLastStep);
		}
	}
	if (dir.y == 1)
	{
		if (isFalling)
		{
			fall();
		}
		if (isClimbing)
		{
			climbDown();
		}
	}
}

void Mario::jump()
{
	if (jumpCount < jumpLimit)
	{
		moveUp();
		isOnGround = false;
		isJumping = true;
		jumpCount++;
	}
	else
	{
		dir.y = 0;
		isJumping = false;
		jumpCount = 0;
	}
}

// Mario falls down the board, while each fall iteration fall count is incremented.
void Mario::fall()
{
	moveDown();
	fallCount++;
	if (fallCount >= fallLimit)
	{
		isAlive = false;
	}
	if (isOnGround || dir.y == 0)
	{
		isFalling = false;
		fallCount = 0;
	}
}

void Mario::climbUp(bool isLastStep)
{
	if (isLastStep)
	{
		isOnGround = true;
		isClimbing = false;
		onLadder = false;
		moveUp(isLastStep);
	}
	else
	{
		moveUp();
		onLadder = true;
		isClimbing = true;
	}
}

void Mario::climbDown()
{
	moveDown();
	onLadder = true;
	isClimbing = true;
}



