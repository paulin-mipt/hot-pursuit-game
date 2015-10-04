#pragma once

#include <iostream>
#include <vector>
#include <exception>
#include <stdexcept>

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

enum Directions {
	SW = 1, S, SE,
	W, C, E, // `C` for no direction
	NW, N, NE
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

	void die( void );
	void goToStart( void );

	Coordinates getPosition( void );
	Coordinates* move( int );
private:
	Coordinates position;
	Coordinates inertia;
	Coordinates initial_position;
	Coordinates* moveInDirection( Coordinates );
	bool isAlive;
};

