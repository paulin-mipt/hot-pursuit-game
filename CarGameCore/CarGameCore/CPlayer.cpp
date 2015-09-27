#include "CPlayer.h"

Player::Player()
{
	isAlive = true;
	innertion.x = 0;
	innertion.y = 0;
}

Player::Player( const Coordinates& newCoordinates, const bool state ) :
	currentCoordinates( newCoordinates ), isAlive( state ), innertion( 0, 0 )
{
}

Player::~Player()
{
}
