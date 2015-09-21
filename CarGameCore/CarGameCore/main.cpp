#include <string>
#include "CGame.h"

const std::string MAP_PATH = ""; // Path for field-table

int main()
{
	Reader reader;
	Map newMap( reader.readMap( MAP_PATH ) );
	PlayersInfo newPlayersInfo = reader.readPlayers();
	Game newGame( newMap, newPlayersInfo );
	newGame.start();

	return 0;
}