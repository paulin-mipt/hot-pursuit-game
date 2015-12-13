﻿#include <vector>
#include <algorithm>

#include "Core/Game.h"
#include "AI/IPlayerState.h"
#include "AI/IMap.h"

HINSTANCE hInstanceDLLLibrary = NULL;

typedef int( __cdecl *STRATEGY_PROC )(const IMap &_map, const std::vector<std::shared_ptr<IPlayerState>> &_playerStates, int curPlayerPosition);
typedef IPlayerState*(__cdecl *PLAYER_STATE_FACTORY_PROC)(int x, int y, int xVelocity, int yVelocity);

typedef IMap*(__cdecl *MAP_DEFAULT_FACTORY_PROC)();
typedef IMap*(__cdecl *MAP_FACTORY_PROC)(const std::vector< std::vector < int > > &inputCells,
	const std::pair< int, int > &_leftFinishPoint,
	const std::pair< int, int > &_rightFinishPoint);


namespace Core {
	namespace {
		bool inBoxOnAxis( int firstPoint, int secondPoint, int thirdPoint, int forthPoint )
		{
			if( firstPoint > secondPoint ) {
				std::swap( firstPoint, secondPoint );
			}
			if( thirdPoint > forthPoint ) {
				std::swap( thirdPoint, forthPoint );
			}
			return max( firstPoint, thirdPoint ) <= min( secondPoint, forthPoint );
		}

		int area( const CCoordinates& firstPoint, const CCoordinates& secondPoint, const CCoordinates& thirdPoint )
		{
			return (secondPoint.x - firstPoint.x) * (thirdPoint.y - firstPoint.y)
				- (secondPoint.y - firstPoint.y) * (thirdPoint.x - firstPoint.x);
		}

		bool isIntersects(
			const CCoordinates& firstPoint,
			const CCoordinates& secondPoint,
			const CCoordinates& thirdPoint,
			const CCoordinates& fourthPoint )
		{
			return inBoxOnAxis( firstPoint.x, secondPoint.x, thirdPoint.x, fourthPoint.x )
				&& inBoxOnAxis( firstPoint.y, secondPoint.y, thirdPoint.y, fourthPoint.y )
				&& (area( firstPoint, secondPoint, thirdPoint )
					* area( firstPoint, secondPoint, fourthPoint )) <= 0
				&& (area( thirdPoint, fourthPoint, firstPoint )
					* area( thirdPoint, fourthPoint, secondPoint )) <= 0;
		}
	}

	CGame::CGame( const CMap& newMap, const std::vector<CPlayer>& playersInfo, const CUIManager* _manager ) :
		map( newMap ),
		numOfDeadPlayers( 0 ),
		players( playersInfo ),
		manager( _manager )
	{
	}

	int CGame::finishLineIntersectsWithPlayer( const CPlayer& player ) const
	{
		// Происходит проверка:
		// 1. Проекции отрезков на оси пересекаются
		// 2. Считается ориентированная площадь треугольников. Нужно, чтобы эти площади были разных знаков.
		CCoordinates playersPreviousCoordinates = player.GetPreviousPosition();
		CCoordinates playersCoordinates = player.GetPosition();

		if( playersCoordinates == playersPreviousCoordinates )
			return 0;

		if( isIntersects( playersPreviousCoordinates, playersCoordinates, map.GetFinishLine().first, map.GetFinishLine().second ) ) {
			CCoordinates normalVectorCoordinates( map.GetFinishLine().second.x - map.GetFinishLine().first.x,
				map.GetFinishLine().second.y - map.GetFinishLine().first.y );
			if( area( map.GetFinishLine().first, playersCoordinates, map.GetFinishLine().second ) *
				area( map.GetFinishLine().first, normalVectorCoordinates, map.GetFinishLine().second ) >= 0 &&
				area( map.GetFinishLine().first, playersPreviousCoordinates, map.GetFinishLine().second ) *
				area( map.GetFinishLine().first, normalVectorCoordinates, map.GetFinishLine().second ) < 0 )
				return 1;
			return -1;
		}
		return 0;
	}

	const CPlayer* CGame::handleFinishLineIntersections()
	{
		for( int i = 0; i < players.size(); ++i ) {
			if( finishLineIntersectsWithPlayer( players[i] ) == -1 ) {
				players[i].StartCheating();
			}
			if( finishLineIntersectsWithPlayer( players[i] ) == 1 ) {
				if( players[i].IsCheating() ) {
					players[i].StopCheating();
				} else {
					return &players[i];
				}
			}
		}
		return nullptr;
	}

	bool CGame::playerOutOfTrack( const CPlayer& player ) const
	{
		CCoordinates playersPreviousCoordinates = player.GetPreviousPosition();
		CCoordinates playersCoordinates = player.GetPosition();

		int minX = min( playersPreviousCoordinates.x, playersCoordinates.x ),
			maxX = max( playersPreviousCoordinates.x, playersCoordinates.x ),
			minY = min( playersPreviousCoordinates.y, playersCoordinates.y ),
			maxY = max( playersPreviousCoordinates.y, playersCoordinates.y );

		CCoordinates realCoordinates( playersCoordinates.x * 10 + 5, playersCoordinates.y * 10 + 5 ),
			realPreviousCoordinates( playersPreviousCoordinates.x * 10 + 5, playersPreviousCoordinates.y * 10 + 5 );

		for( int i = minX; i <= maxX; ++i ) {
			for( int j = minY; j <= maxY; ++j ) {
				if( map.IsEmpty( i, j ) ) {
					continue;
				}
				CCoordinates firstPoint( i * 10, j * 10 ),
					secondPoint( (i + 1) * 10, j * 10 ),
					thirdPoint( (i + 1) * 10, (j + 1) * 10 ),
					fourthPoint( i * 10, (j + 1) * 10 );

				if( isIntersects( realPreviousCoordinates, realCoordinates, firstPoint, secondPoint ) ||
					isIntersects( realPreviousCoordinates, realCoordinates, secondPoint, thirdPoint ) ||
					isIntersects( realPreviousCoordinates, realCoordinates, thirdPoint, fourthPoint ) ||
					isIntersects( realPreviousCoordinates, realCoordinates, fourthPoint, firstPoint ) ) {
					return true;
				}
			}
		}
		return false;
	}

	class floatVector
	{
	public:
		floatVector()
		{
			x = 0;
			y = 0;
		}

		floatVector( const CCoordinates& coord )
		{
			x = coord.x;
			y = coord.y;
		}

		float length()
		{
			return sqrt( x * x + y * y );
		}

		static float scalarMult( const floatVector& v1, const floatVector& v2 )
		{
			return v1.x * v2.x + v1.y * v2.y;
		}

		floatVector& operator-( const floatVector& v2 )
		{
			floatVector result;
			result.x = x - v2.x;
			result.y = y - v2.y;
			return result;
		}

		floatVector& operator+( const floatVector& v2 )
		{
			floatVector result;
			result.x = x + v2.x;
			result.y = y + v2.y;
			return result;
		}

		floatVector& operator*( const float scalar )
		{
			floatVector result;
			result.x = x * scalar;
			result.y = y * scalar;
			return result;
		}

		float x;
		float y;
	};



	floatVector getSpeed( CCoordinates& coord1, CCoordinates& coord2 )
	{
		floatVector result;
		result.x = (( float )(coord1.x - coord2.x)) / 100;
		result.y = (( float )(coord1.y - coord2.y)) / 100;
		return result;
	}

	void CGame::findCollisions()
	{
		for( size_t i = 0; i < players.size(); ++i ) {
			for( size_t j = i + 1; j < players.size(); ++j ) {
				if( players[i].IsAlive() && players[j].IsAlive() ) {
					CCoordinates prevCoordPlayer1 = players[i].GetPreviousPosition();
					CCoordinates prevCoordPlayer2 = players[j].GetPreviousPosition();
					CCoordinates coordPlayer1 = players[i].GetPosition();
					CCoordinates coordPlayer2 = players[j].GetPosition();

					floatVector speedPlayer1 = getSpeed( coordPlayer1, prevCoordPlayer1 );
					floatVector speedPlayer2 = getSpeed( coordPlayer2, prevCoordPlayer2 );

					floatVector startDiff( prevCoordPlayer1 - prevCoordPlayer2 );

					float cosAngle = floatVector::scalarMult( speedPlayer1, speedPlayer2 )
						/ speedPlayer1.length()
						/ speedPlayer2.length();
					float criticalDistance = 0;
					if( cosAngle > sqrt( 2 ) / 2 ) {
						criticalDistance = 0.25 + 0.25;
					} else if( cosAngle >= -sqrt( 2 ) / 2 && cosAngle <= sqrt( 2 ) / 2 ) {
						criticalDistance = 0.5 + 0.25;
					} else {
						criticalDistance = 0.5 + 0.5;
					}

					floatVector speedDiff = speedPlayer1 - speedPlayer2;

					for( int t = 0; t < 100; t++ ) {
						floatVector distDiff = speedDiff * t;
						floatVector sumDiff = startDiff + distDiff;
						if( criticalDistance > sumDiff.length() ) {
							collidedPlayers.insert( players[i] );
							collidedPlayers.insert( players[j] );
						}
					}
				}
			}
		}
	}

	void CGame::findCrashes()
	{
		for( auto player : players ) {
			if( !player.IsAlive() ) {
				continue;
			}
			if( playerOutOfTrack( player ) && player.IsAlive() ) {
				crashedPlayers.insert( player );
			}
		}
	}

	void CGame::turnOfPlayer( CPlayer& player )
	{
		int direction;
		std::vector<CCoordinates> possibleMoves;
		switch( player.GetType() ) {
			case USER:
				//вывести возможные ходы
				possibleMoves = player.PossibleMoves( map.GetSize() );
				manager->MarkPossibleMoves( possibleMoves );
				//manager-->possibleMoves
				direction = manager->GetDirection( possibleMoves, player.GetInertia(), player.GetPosition() );
				manager->UnMarkPossibleMoves( possibleMoves );
				break;
			case AI:
			{
				if( !hInstanceDLLLibrary ) hInstanceDLLLibrary = LoadLibrary( TEXT( "StrategyDLL.dll" ) );
				STRATEGY_PROC StrategyFunc = ( STRATEGY_PROC )GetProcAddress( hInstanceDLLLibrary, "StrategyFunc" );
				PLAYER_STATE_FACTORY_PROC GetPlayerState = ( PLAYER_STATE_FACTORY_PROC )GetProcAddress( hInstanceDLLLibrary, "GetPlayerState" );
				MAP_FACTORY_PROC GetMap = ( MAP_FACTORY_PROC )GetProcAddress( hInstanceDLLLibrary, "GetMap" );
				// Map map;

				CField field = map.GetField();
				CSize sizemap = map.GetSize();
				std::vector< std::vector< int > > mapForAI( sizemap.second );

				for( int i = 0; i < sizemap.second; ++i ) {
					for( int j = 0; j < sizemap.first; ++j ) {
						mapForAI[i].push_back( field[i][j] );
					}
				}
				CCoordinates firstFinishPoint = map.GetFinishLine().first;
				CCoordinates secondFinishPoint = map.GetFinishLine().second;

				std::shared_ptr< IMap > mapPtr( GetMap(
					mapForAI,
					std::make_pair(
					firstFinishPoint.y,
					firstFinishPoint.x ),
					std::make_pair(
					secondFinishPoint.y,
					secondFinishPoint.x )
					)
					);
				std::vector< std::shared_ptr< IPlayerState > > playerStates;

				for( int i = 0; i < players.size(); ++i ) {
					if( !players[i].IsAlive() ) continue;

					CCoordinates currentPosition = players[i].GetPosition();
					CCoordinates previuosPosition = players[i].GetPreviousPosition();

					int xVelocity = currentPosition.x - previuosPosition.x;
					int yVelocity = currentPosition.y - previuosPosition.y;

					std::shared_ptr<IPlayerState> playerStatePtr(
						GetPlayerState(
						currentPosition.y,
						currentPosition.x,
						yVelocity,
						xVelocity
						)
						);
					playerStates.push_back( playerStatePtr );
				}

				direction = StrategyFunc( *mapPtr, playerStates, player.GetNumber() );
				break;
			}
			default:
				throw std::runtime_error( "Invalid type of player. Please, don't cheat." );
		}
		if( player.DirectionIsValid( Direction( direction ), map.GetSize() ) ) {
			player.Move( Direction( direction ) );
			return;
		}
		player.Move( Direction( direction ) );
		player.Die();
		crashedPlayers.insert( player );
	}

	void CGame::Start()
	{
		const CPlayer* winner = nullptr;
		manager->InitMap( map, players, map.GetStartLine(), map.GetFinishLine() );

		do {
			for( size_t i = 0; i < players.size(); ++i ) {

				if( players[i].IsAlive() ) {
					turnOfPlayer( players[i] );
				}
			}

			manager->Move( players );

			findCollisions();
			findCrashes();

			for( auto crashedPlayer : crashedPlayers ) {
				auto it = collidedPlayers.find( crashedPlayer );
				if( it != collidedPlayers.end() ) {
					collidedPlayers.erase( it );
				}
			}
			for( auto collidedPlayer : collidedPlayers ) {
				players[collidedPlayer.GetNumber()].GoToStart();
			}
			for( auto crashedPlayer : crashedPlayers ) {
				players[crashedPlayer.GetNumber()].Die();
			}
			if( !collidedPlayers.empty() ) {
				manager->ShowCollisions( collidedPlayers );
			}
			if( !crashedPlayers.empty() ) {
				manager->ShowCrashes( crashedPlayers );
			}

			numOfDeadPlayers += crashedPlayers.size();
			if( numOfDeadPlayers == players.size() ) {
				break;
			}

			collidedPlayers.clear();
			crashedPlayers.clear();
		} while( (winner = handleFinishLineIntersections()) == nullptr );

		finish( winner );
	}

	void CGame::finish( const CPlayer* winnerPtr )
	{
		manager->FinishGame();
		manager->ShowGameResult( winnerPtr );
	}
}