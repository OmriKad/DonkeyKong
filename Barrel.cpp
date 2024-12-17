#include "Barrel.h"

// responsible for the movemnt logic of a single barrel on the screen
void Barrel::move()
{
	if (!getExploded())
	{
		erase();
		if ((!pBoard->is_pos_legal(x + dir.x, y)))
		{
			explode();
			return;
		}
		char tileBelow = pBoard->getChar(x, y + 1);
		switch (tileBelow)
		{
		case ' ':
			if (fallDelayCounter < fallDelay) // making sure the fall is reasonably slow
			{
				fallDelayCounter++;
				break;
			}
			fallDelayCounter = 0;
			setDir(0, 1);
			addFallCount();
			if (getFallCount() >= getFallLimit())
				setNeedToExploade(true);
			updateXY();
			break;
		case '>':
			setDir(1, 0);
			setLastDirX(1);
			if (getNeedToExploade())
			{
				explode();
				return;
			}
			resetFallCount();
			updateXY();
			break;
		case '<':
			setDir(-1, 0);
			setLastDirX(-1);
			if (getNeedToExploade())
			{
				explode();
				return;
			}
			resetFallCount();
			updateXY();
			break;
		case '=':
		case 'Q':
			setDir(getLastDirX(), 0);
			if (getNeedToExploade())
			{
				explode();
				return;
			}
			resetFallCount();
			updateXY();
			break;
		}
		draw();
	}
}
