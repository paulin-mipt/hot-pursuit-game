#pragma once

#include "Core/Map.h"
#include "Core/Player.h"
#include "Core/Reader.h"

namespace Core {
	struct CPointsInformation {
		CPointsInformation( const bool condition, const CCoordinates& oldCoordinates, const CCoordinates& newCoordinate ) :
			isAlive( condition ), previousCoordinates( oldCoordinates ), currentCoordinates( newCoordinate )
		{}

		bool isAlive;
		CCoordinates previousCoordinates;
		CCoordinates currentCoordinates;
	};


	class CGame {
	public:
		CGame( const CMap& map, const CPlayersInfo& playersInfo, const CLine& startLine, const CReader& reader );

		~CGame();

		void start();
		void finish( size_t winner );
		void fatalFinish();
		CPointsInformation getPlayersBasePoints( size_t num ); // Отдаем Frontend у

	private:
		CMap map;
		CReader reader;
		size_t numOfDeadPlayers;
		std::vector<CPlayer> players;
		CLine startLine;

		int getPlayerOnFinish();
		bool startLineIntersectsWithPlayer( size_t num );
		void turnOfPlayer( size_t num );
		int playerCrashedIntoCar( size_t num );
		bool playerOutOfTrack( size_t num );
		void initPlayersPositionsInMap();
		void clearPlayersState( size_t num );
		void paintPlayersState( size_t num );
	};
}