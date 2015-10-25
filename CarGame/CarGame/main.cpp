#include <string>
#include <iostream>

#include "GlobalDefinitions.h"
#include "Core/Game.h"

int main()
{
	using namespace Core;

	CReader reader;
	try {
		CMap newMap( reader.readMap( RESOURCE_DIRECTORY + "Maps\\map.txt" ) );
		CLine startLine = reader.readLine();
		CPlayersInfo newPlayersInfo = reader.readPlayers();
		CGame newGame( newMap, newPlayersInfo, startLine, reader );
		newGame.start();
	} catch( std::exception const &e ) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}