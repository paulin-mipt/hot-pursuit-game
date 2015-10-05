#pragma once

#include <fstream>
#include <iostream>
#include "CPlayer.h"
#include <exception>
#include <string>

typedef std::vector< std::vector<size_t> > Field;

struct Line {
	Line()
	{
	}

	Line( Coordinates x, Coordinates y ) :
		firstPoint( x ), secondPoint( y )
	{
	}

	Coordinates firstPoint;
	Coordinates secondPoint;
};

class Reader {

public:
	Reader();

	~Reader();

	Field readMap( const std::string& path );

	PlayersInfo readPlayers();

	int readPlayersChoice( size_t num ); // todo: сделать параметром номер игрока, чтобы обращаться к нему при считывани его хода

	Line readLine();
};