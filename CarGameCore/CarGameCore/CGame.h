#pragma once

#include "CMap.h"
#include "CPlayer.h"
#include "CReader.h"
#include <vector>
#include <iostream>

class Game {
public:
	Game();

	Game( const Map& map, const PlayersInfo& playersInfo );

	~Game();

	void start();

private:
	Map map;
	std::vector<Player> players;
};