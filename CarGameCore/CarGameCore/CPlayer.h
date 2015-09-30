#pragma once

#include <vector>

struct Coordinates {
	Coordinates( int newX, int newY ) :
		x( newX ), y( newY )
	{
	}

	Coordinates()
	{
	}

	int x;
	int y;
};

struct PlayersInfo {
	PlayersInfo()
	{
		numberOfPlayers = 0;
	}

	size_t numberOfPlayers;
	std::vector<Coordinates> positions;
};

class Player {
public:
	Player();

	Player( const Coordinates& coordinates, const bool isAlive );

	~Player();

private:
	Coordinates currentCoordinates;
	Coordinates innertion;
	bool isAlive;
};