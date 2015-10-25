#include "Core/Player.h"

namespace Core {
	CPlayer::CPlayer( const CCoordinates& newCoordinates, const bool state ) :
		position( newCoordinates ),
		inertia( 0, 0 ),
		initialPosition( newCoordinates ),
		previousPosition( newCoordinates ),
		isAlive( state ),
		firstStep( true ),
		secondStep( true )
	{}

	CCoordinates CPlayer::getPosition()
	{
		return this->position;
	}

	void CPlayer::goToStart()
	{
		this->position = this->initialPosition;
		this->previousPosition = this->initialPosition;
		this->inertia.x = 0;
		this->inertia.y = 0;
		this->firstStep = true;
		this->secondStep = true;
	}

	CCoordinates CPlayer::convertFromDirectionCode( int directionCode )
	{
		CCoordinates direction( 0, 0 );
		switch( directionCode ) {
			case SW:
				direction.x = -1;
				direction.y = +1;
				break;
			case S:
				direction.x = 0;
				direction.y = +1;
				break;
			case SE:
				direction.x = +1;
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
				direction.y = 0;
				break;
			case NW:
				direction.x = -1;
				direction.y = -1;
				break;
			case N:
				direction.x = 0;
				direction.y = -1;
				break;
			case NE:
				direction.x = +1;
				direction.y = -1;
				break;
			default:
				throw std::invalid_argument( "Unknown direction code" );
		}
		return direction;
	}

	void CPlayer::move( int direction_code, CSize size )
	{
		CCoordinates direction = convertFromDirectionCode( direction_code );
		this->moveInDirection( direction );
	};

	void CPlayer::moveInDirection( CCoordinates direction )
	{
		CCoordinates move( inertia.x + direction.x, inertia.y + direction.y );

		inertia = move;
		previousPosition = position;
		position.x += move.x;
		position.y += move.y;
	}

	CCoordinates CPlayer::getPreviousPosition()
	{
		return this->previousPosition;
	};

	void CPlayer::die()
	{
		isAlive = false;
	};

	bool CPlayer::wasFirstStep()
	{
		return firstStep;
	}

	bool CPlayer::wasSecondStep()
	{
		return secondStep;
	}

	void CPlayer::makeFirstStep()
	{
		firstStep = false;
	}

	void CPlayer::makeSecondStep()
	{
		secondStep = false;
	}

	bool CPlayer::directionIsValid( int directionCode, const CSize& size )
	{
		CCoordinates direction = convertFromDirectionCode( directionCode );
		return 0 <= (direction + position + inertia).x && (direction + position + inertia).x <= size.first - 1 &&
			0 <= (direction + position + inertia).y && (direction + position + inertia).y <= size.second - 1;
	}

	bool CPlayer::playerIsAlive()
	{
		return isAlive;
	}
}