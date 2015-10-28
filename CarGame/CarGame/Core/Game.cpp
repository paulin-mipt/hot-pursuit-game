#include <vector>
#include <algorithm>
#include <iostream>

#include "Core/Game.h"

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
			return std::max( firstPoint, thirdPoint ) <= std::min( secondPoint, forthPoint );
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

	CGame::CGame( const CMap& newMap, size_t playersNumber ) :
		map( newMap ),
		numOfDeadPlayers( 0 )
	{
		if (playersNumber > map.GetStartPoints().size() ) {
			throw std::invalid_argument( std::string( "Too many players. This map is for " ) + std::to_string( map.GetStartPoints().size() ) + " players or less." );
		}
		for( int i = 0; i < playersNumber; ++i ) {
			players.push_back( CPlayer( map.GetStartPoints()[i], i ) );
		}
	}

	int CGame::finishLineIntersectsWithPlayer( const CPlayer& player ) const
	{
		// Происходит проверка:
		// 1. Проекции отрезков на оси пересекаются
		// 2. Считается ориентированная площадь треугольников. Нужно, чтобы эти площади были разных знаков.
		CCoordinates playersPreviousCoordinates = player.GetPreviousPosition();
		CCoordinates playersCoordinates = player.GetPosition();
		return isIntersects( playersPreviousCoordinates, playersCoordinates, map.GetFinishLine().first, map.GetFinishLine().second );
	}

	const CPlayer* CGame::handleFinishLineIntersections()
	{
		for( auto player : players ) {
			if( finishLineIntersectsWithPlayer( player ) == -1 ) {
				player.StartCheating();
			}
			if( finishLineIntersectsWithPlayer( player ) == 1 ) {
				if (player.IsCheating() ) {
					player.StopCheating();
				} else {
					return &player;
				}
			}
		}
		return nullptr;
	}

//	int CGame::playerCrashedIntoCar( size_t num ) const
//	{
//		for( size_t i = 0; i < players.size(); ++i ) {
//			if( i != num && players[i].GetPosition() == players[num].GetPosition() ) {
//				return int( i );
//			}
//		}
//		return -1;
//	}

	bool CGame::playerOutOfTrack( const CPlayer& player ) const
	{
		CCoordinates playersPreviousCoordinates = player.GetPreviousPosition();
		CCoordinates playersCoordinates = player.GetPosition();

		int minX = std::min( playersPreviousCoordinates.x, playersCoordinates.x ),
			maxX = std::max( playersPreviousCoordinates.x, playersCoordinates.x ),
			minY = std::min( playersPreviousCoordinates.y, playersCoordinates.y ),
			maxY = std::max( playersPreviousCoordinates.y, playersCoordinates.y );

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

	void CGame::findCollisions()
	{
		for( size_t i = 0; i < players.size(); ++i ) {
			for( size_t j = i + 1; j < players.size(); ++j ) {
				if ( players[i].GetPosition() == players[j].GetPosition() && players[i].IsAlive() && players[j].IsAlive() ) {
					collidedPlayers.insert( players[i] );
					collidedPlayers.insert( players[j] );
				}
			}
		}
	}

	void CGame::findCrashes()
	{
		for( auto player : players ) {
			if( playerOutOfTrack( player ) ) {
				crashedPlayers.insert( player );
			}
		}
	}

	void CGame::turnOfPlayer( CPlayer& player )
	{
		// взять у UI направление
//		int direction = reader.readPlayersChoice( num );
		int direction;
		std::cin >> direction;
		if( !player.DirectionIsValid( Direction( direction ), map.GetSize() ) ) {
			player.Die();
			crashedPlayers.insert( player );
			++numOfDeadPlayers;
//			std::cout << "Player " << num + 1 << " is dead" << std::endl;
			return;
		}

		player.Move( Direction( direction ), map.GetSize() );

		// заменено на проверку после отрисовки столкновений всех игроков
//		int crashedPlayer = playerCrashedIntoCar( num );
//		if( crashedPlayer != -1 ) {
//			players[num].GoToStart();
////			clearPlayersState( crashedPlayer );
//			players[crashedPlayer].GoToStart();
////			paintPlayersState( crashedPlayer );
//			return;
//		}

		// заменено на проверку после отрисовки всех вылетевших за пределы трассы игроков
//		if( playerOutOfTrack( num ) ) {
//			players[num].Die();
//			++numOfDeadPlayers;
//			std::cout << "Player " << num + 1 << " is dead" << std::endl;
//			return;
//		}
	}

//	void CGame::initPlayersPositionsInMap()
//	{
//		for( size_t i = 0; i < players.size(); ++i ) {
//			CCoordinates currentCoordinates = players[i].GetPosition();
//			map.SetPosition( currentCoordinates.x, currentCoordinates.y );
//		}
//	}
//	
//	void CGame::clearPlayersState( size_t num ) // Стирает изображение игрока с поля
//	{
//		CCoordinates old = players[num].GetPreviousPosition();
//		CCoordinates now = players[num].GetPosition();
//		map.ClearPosition( old.x, old.y );
//		map.ClearPosition( now.x, now.y );
//	}
//
//	void CGame::paintPlayersState( size_t num ) // Рисует изображение игрока на поле
//	{
//		CCoordinates previousCoordinates = players[num].GetPreviousPosition();
//		CCoordinates currentCoordinates = players[num].GetPosition();
//		map.SetPosition( previousCoordinates.x, previousCoordinates.y );
//		map.SetPosition( currentCoordinates.x, currentCoordinates.y );
//	}

	void CGame::Start()
	{
		std::cout << "Game has been started." << std::endl;
		const CPlayer* winner = nullptr;
		// сообщение UI, чтобы он создал карту и расставил игроков
//		initPlayersPositionsInMap(); // На карте проставляются координаты машинок
		while( (winner = handleFinishLineIntersections()) == nullptr ) { // -1 - никто пока к финишу не пришел
			for( size_t i = 0; i < players.size(); ++i ) {
				// в далёком будущем здесь будет посылаться сообщение UI, чтобы он отрисовал возможные ходы, выделил ходящего игрока и т.д.
				if( players[i].IsAlive() ) {
//					clearPlayersState( i );
					turnOfPlayer( players[i] ); // AI: Если будет AI, здесь он запускается (перед этим, занести его в players[])
//					paintPlayersState( i );
//					map.print();  // Вывод поля на консоль
				}
			}

			// сообщение UI, чтобы он отрисовал ход

			findCollisions();
			findCrashes();
			for( auto collidedPlayer : collidedPlayers ) {
				if ( crashedPlayers.find( collidedPlayer ) != crashedPlayers.end() ) {
					collidedPlayer.GoToStart();
					// сообщение UI, чтобы он отрисовал исчезновение игрока и появление на старте
				}
			}
			for ( auto crashedPlayer : crashedPlayers ) {
				crashedPlayer.Die();
				// сообщение UI, чтобы он отрисовал исчезновение игрока и появление на старте
			}
			if( numOfDeadPlayers == players.size() ) {
				break;
			}
		}
		finish( winner );
	}

	void CGame::finish( const CPlayer* winner )
	{
		// сообщение UI, чтобы вывел всё на экран
		if (winner == nullptr ) {
			std::cout << "All players are dead! Congratulations ^_^" << std::endl;
		} else {
			std::cout << "Player number " << winner->GetNumber() + 1 << " is winner! Congratulations!!!" << std::endl;
		}
	}

//	CPointsInformation CGame::GetPlayersBasePoints( size_t num )  // нужно для UI
//	{
//		if( num >= players.size() ) {
//			throw std::invalid_argument( "CGame::GetPlayersBasePoints: num > number of players" );
//		}
//		return CPointsInformation( players[num].IsAlive(), players[num].GetPreviousPosition(), players[num].GetPosition() );
//	}
}