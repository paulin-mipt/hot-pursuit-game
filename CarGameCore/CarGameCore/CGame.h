#pragma once

#include "CMap.h"
#include "CPlayer.h"
#include "CReader.h"
#include <vector>
#include <iostream>

class Game {
public:
	Game();

	Game( const Map& map, const PlayersInfo& playersInfo, const Line& startLine, const Reader& reader );

	~Game();

	void start();
	void finish( size_t winner );

private:
	Map map;
	Reader reader;
	std::vector<Player> players;
	Line startLine;

	int getPlayerOnFinish( bool& begining );
	void turnOfPlayer( size_t number );
};