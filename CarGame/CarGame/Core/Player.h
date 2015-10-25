#pragma once

#include <utility>
#include <vector>

namespace Core {
	typedef std::pair<size_t, size_t> CSize;

	struct CCoordinates {
		CCoordinates( int newX, int newY ) :
			x( newX ),
			y( newY )
		{}

		bool operator == ( const CCoordinates &point ) const
		{
			return this->x == point.x && this->y == point.y;
		}

		CCoordinates operator + ( const CCoordinates &point ) const
		{
			return CCoordinates( this->x + point.x, this->y + point.y );
		}

		int x;
		int y;
	};

	enum Directions {
		SW = 1, S, SE,
		W, C, E, // `C` for no direction
		NW, N, NE
	};

	struct CPlayersInfo {
		CPlayersInfo()
		{
			numberOfPlayers = 0;
		}

		size_t numberOfPlayers;
		std::vector<CCoordinates> positions;
	};

	class CPlayer {
	public:
		CPlayer( const CCoordinates& coordinates, const bool isAlive );

		void die();
		void goToStart();

		CCoordinates getPosition();
		void move( int, CSize );
		CCoordinates getPreviousPosition();
		bool wasFirstStep();
		bool wasSecondStep();
		void makeFirstStep();
		void makeSecondStep();
		bool directionIsValid( int direction, const CSize& size );
		bool playerIsAlive();

	private:
		CCoordinates position;
		CCoordinates inertia;
		CCoordinates initialPosition; // Для возвращения на старт, после столкновения с машиной
		CCoordinates previousPosition;
		bool isAlive;
		bool firstStep;
		bool secondStep;

		void moveInDirection( CCoordinates );
		CCoordinates convertFromDirectionCode( int );
	};
}