#include "FileInputGame.h"
#include "HumanInputGame.h"
#include "utils.h"
#include "Game.h"

int main(int argc, char** argv)
{
	bool isLoad = false;
	bool isSave = false;
	bool isSilent = false;
	if (argc > 1)
	{
		bool retFlag;
		int retVal = checkArgs(argc, argv, isLoad, isSave, isSilent, retFlag);
		if (retFlag) return retVal;
	}
	if (isSave)
	{
		HumanInputGame game(isSave);
		game.game();
	}
	else if (isLoad)
	{
		FileInputGame game(isSilent);
		game.game();
	}
	else
	{
		Game game;
		game.game();
	}
}

