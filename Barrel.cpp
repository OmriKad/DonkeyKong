#include "Barrel.h"

void Barrel::move()
{
	if (!getExploded())
	{
		Sleep(50);
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
