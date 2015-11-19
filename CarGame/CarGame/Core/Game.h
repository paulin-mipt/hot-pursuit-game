#pragma once

#include <set>

#include "Core/Map.h"
#include "Core/Player.h"
#include "UIManager.h"

namespace Core {
	class CGame {
	public:
		CGame( const CMap& map, const std::vector<CPlayer>& playersInfo, const CUIManager* _manager );

		void Start();

	private:
		CMap map;
		std::vector<CPlayer> players;
		const CUIManager* manager;

		void handleFinishLineIntersections();
		// требование к возвращаемому значению:
		//	-1 - если пересекли финишную черту в неправильную сторону
		//	0 - не пересекли
		//	1 - пересекли черту в правильную сторону
		int finishLineIntersectsWithPlayer( const CPlayer& player ) const;
		void turnOfPlayer( CPlayer& player, std::set<CPlayer*>& crashedPlayers );
		bool playerOutOfTrack( const CPlayer& player ) const;
		void handleCrashes( const std::set<CPlayer*>& crashedPlayers, int& deadPlayersCount ) const;
		void findCollisions( std::set<CPlayer*>& crashedPlayers );
		void findCollisionsForPlayer( int playerId, std::set<CPlayer*>& crashedPlayers );
		void findCrashes( std::set<CPlayer*>& crashedPlayers );
		void findCrashesForPlayer( CPlayer& player, std::set<CPlayer*>& crashedPlayers ) const;
		void findWinners( std::vector<CPlayer>& winners ) const;
		void finish( const std::vector<CPlayer>& winners ) const;
	};
}