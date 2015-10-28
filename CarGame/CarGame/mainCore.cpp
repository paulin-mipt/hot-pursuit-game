#include <string>
#include <iostream>

#include "Core/Reader.h"
#include "Core/Game.h"
#include "GlobalDefinitions.h"

int main()
{
	using namespace Core;

	CReader reader;
	try {
		CMap map = reader.ReadMap( RESOURCE_DIRECTORY + "Maps\\map.txt" );
//		CLine startLine = reader.readLine(std::cin); // не очень. нужно переделать.
//		CPlayersInfo newPlayersInfo = reader.ReadPlayers( RESOURCE_DIRECTORY + "Players.txt" );
//		CGame newGame( newMap, newPlayersInfo, startLine, reader );

		size_t playerCount;
		std::cin >> playerCount; // берём количество игроков у UI
		CGame game( map, playerCount );
		game.Start();
	} catch( std::exception const &e ) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}