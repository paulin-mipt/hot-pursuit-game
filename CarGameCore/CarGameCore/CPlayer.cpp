#include "CPlayer.h"

Player::Player()
{
	isAlive = true;
	inertia.x = 0;
	inertia.y = 0;
}

Player::Player( const Coordinates& newCoordinates, const bool state ) :
	initial_position( newCoordinates ), previous_position( newCoordinates ), position( newCoordinates ), isAlive( state )
{
}
Coordinates Player::getPosition()
{
	return this->position;
};

void Player::goToStart()
{
	this->position = this->initial_position;
};

std::tr1::shared_ptr<Coordinates> Player::move( int direction_code )
{
	Coordinates direction;

	switch( direction_code ) {
		case SW:
			direction.x = -1;
			direction.y = -1;
			break;
		case S:
			direction.x = 0;
			direction.y = -1;
			break;
		case SE:
			direction.x = -1;
			direction.y = +1;
			break;
		case W:
			direction.x = -1;
			direction.y = 0;
			break;
		case C:
			direction.x = 0;
			direction.y = 0;
			break;
		case E:
			direction.x = +1;
			direction.y = +0;
			break;
		case NW:
			direction.x = -1;
			direction.y = +1;
			break;
		case N:
			direction.x = 0;
			direction.y = +1;
			break;
		case NE:
			direction.x = +1;
			direction.y = +1;
			break;
		default:
			throw std::invalid_argument( "Unknown direction code" );
	}

	return this->moveInDirection( direction );
};

std::tr1::shared_ptr<Coordinates> Player::moveInDirection( Coordinates direction )
{

	Coordinates move;
	move.x = this->inertia.x + direction.x;
	move.y = this->inertia.y + direction.y;

	Coordinates pure_inertial;
	pure_inertial.x = this->position.x + this->inertia.x;
	pure_inertial.y = this->position.y + this->inertia.y;

	this->inertia = move;
        
        this->previous_position = this->position;

	this->position.x = this->position.x + move.x;
	this->position.y = this->position.y + move.y;


        std::tr1::shared_ptr<Coordinates> result(new Coordinates[2]);

	result[0] = move;
	result[1] = pure_inertial;

	return result;

};

void Player::die()
{
	isAlive = false;
};
