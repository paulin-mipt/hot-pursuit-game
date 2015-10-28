#pragma once

#include <set>

#include "Core/Map.h"
#include "Core/Player.h"

namespace Core {
	//	struct CPointsInformation {
	//		CPointsInformation( const bool condition, const CCoordinates& oldCoordinates, const CCoordinates& newCoordinate ) :
	//			isAlive( condition ),
	//			previousCoordinates( oldCoordinates ),
	//			currentCoordinates( newCoordinate )
	//		{}
	//		
	//		bool isAlive;
	//		CCoordinates previousCoordinates;
	//		CCoordinates currentCoordinates;
	//	};

	class CGame {
	public:
		CGame( const CMap& map, size_t playersNumber ); // надо протащить здесь UI

		void Start();
		//		CPointsInformation GetPlayersBasePoints( size_t num ); // Отдаем UI

	private:
		CMap map;
		size_t numOfDeadPlayers;
		std::vector<CPlayer> players;
		// все игроки, которые влетели друг в друга
		std::set<CPlayer> collidedPlayers;
		std::set<CPlayer> crashedPlayers;

		const CPlayer* handleFinishLineIntersections();
		// -1 - если пересекли финишную черту в неправильную сторону, 0 - не пересекли, 1 - в правильную сторону
		int finishLineIntersectsWithPlayer( const CPlayer& player ) const;
		void turnOfPlayer( CPlayer& player );
//		int playerCrashedIntoCar( size_t num ) const;
		bool playerOutOfTrack( const CPlayer& player ) const;
		void findCollisions();
		void findCrashes();
		void finish( const CPlayer* player = nullptr );
		//		void initPlayersPositionsInMap();
		//		void clearPlayersState( size_t num );
		//		void paintPlayersState( size_t num );
	};
}