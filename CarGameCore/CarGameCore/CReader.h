#pragma once

#include <fstream>
#include <iostream>
#include "CPlayer.h"
#include <exception>
#include <string>

typedef std::vector< std::vector<size_t> > Field;

class Reader {

public:
	Reader();

	~Reader();

	Field readMap( const std::string& path );

	PlayersInfo readPlayers();

	Coordinates readPlayersChoice();
};