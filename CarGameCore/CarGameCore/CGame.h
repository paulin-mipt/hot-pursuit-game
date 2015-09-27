#pragma once

#include "CMap.h"
#include "CPlayer.h"
#include "CReader.h"
#include <vector>
#include <iostream>

class Game {
public:
	Game();

	Game( const Map& map, const PlayersInfo& playersInfo, const Reader& reader );

	~Game();

	void start();

private:
	Map map;
	Reader reader;
	std::vector<Player> players;

	bool playersOnFinish();
	void turnOfPlayer( size_t number );
};