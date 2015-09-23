#include "CReader.h"

Reader::Reader()
{
}

Reader::~Reader()
{
}

Field Reader::readMap( const std::string& path )
{
	Field gameField;
	// Reading from file
	return gameField;
}

PlayersInfo Reader::readPlayers()
{
	PlayersInfo info;
	// Reading from console
	return info;
}


Coordinates Reader::readPlayersChoice()
{
	// direction, in which player should go
	return Coordinates( 0, 0 );
}
