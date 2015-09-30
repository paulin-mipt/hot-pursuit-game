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

struct Line {
	Line(Coordinates x, Coordinates y) :
		firstPoint(x), secondPoint(y)
	{
	}

	Coordinates firstPoint;
	Coordinates secondPoint;
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