#pragma once

#include "CMap.h"
#include "CPlayer.h"
#include "CReader.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>

class Game {
public:
	Game();

	Game( const Map& map, const PlayersInfo& playersInfo, const Line& startLine, const Reader& reader );

	~Game();

	void start();
	void finish( size_t winner );
	std::pair<Coordinates, Coordinates> getPlayersBasePoints( size_t num );

private:
	Map map;
	Reader reader;
	std::vector<Player> players;
	Line startLine;

	int getPlayerOnFinish( bool& begining );
	bool startLineIntersectsWithPlayer( size_t num );
	void turnOfPlayer( size_t num );
	int playerCrashedIntoCar( size_t num );
	bool playerOutOfTrack( size_t num );
};