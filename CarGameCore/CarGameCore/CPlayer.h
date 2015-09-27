#pragma once

#include <vector>

struct Coordinates {
	Coordinates( size_t newX, size_t newY ) :
		x( newX ), y( newY )
	{
	}

	Coordinates()
	{
	}

	size_t x;
	size_t y;
};

struct PlayersInfo {
	PlayersInfo()
	{
		numberOfPlayers = 0;
	}

	int numberOfPlayers;
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