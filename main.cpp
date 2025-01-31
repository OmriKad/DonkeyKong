#include "FileInputGame.h"
#include "HumanInputGame.h"

int main(int argc, char** argv) 
{
	bool isLoad = false;
	bool isSave = false;
	bool isSilent = false;
	if (argc > 1)
	{
		isLoad = std::string(argv[1]) == "-load";
		if (argc == 3)
			isSilent = isLoad && argc == 3 && std::string(argv[1]) == "-silent";
		isSave = !isLoad && std::string(argv[1]) == "-save";
	}
	if (argc == 1 || isSave)
	{
		HumanInputGame game(isSave);
		game.game();
	}
	else if (isLoad)
	{
		FileInputGame game(isSilent);
		game.game();
	}
}
