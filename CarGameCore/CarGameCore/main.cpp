#include <string>
#include "CGame.h"

const std::string MAP_PATH = "../map.txt";

int main()
{
	Reader reader;
	try
	{
		Map newMap( reader.readMap( MAP_PATH ) );
		//Read Start Line Here reader.readLine();
		PlayersInfo newPlayersInfo = reader.readPlayers();
		Game newGame( newMap, newPlayersInfo, reader );
		newGame.start();
	}
	catch (std::exception const &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}