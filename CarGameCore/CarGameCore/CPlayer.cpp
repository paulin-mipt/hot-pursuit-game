#include "CPlayer.h"

Player::Player()
{
	isAlive = true;
}

Player::Player( const Coordinates& newCoordinates, const bool state ) :
	currentCoordinates( newCoordinates ), isAlive( state )
{
}

Player::~Player()
{
}
