#include "CGame.h"

Game::Game()
{
}

Game::Game( const Map& newMap, const PlayersInfo& newPlayersInfo, const Line& newStartLine, const Reader& newReader ) :
	map( newMap ), reader( newReader ), startLine( newStartLine )
{

	size_t numOfPlayers = newPlayersInfo.numberOfPlayers;
	for( size_t i = 0; i < numOfPlayers; ++i ) {
		Player newPlayer( newPlayersInfo.positions[i], true );
		players.push_back( newPlayer );
	}
}

Game::~Game()
{
}

bool inBoxOnAxis( int firstPoint, int secondPoint, int thirdPoint, int forthPoint )
{
	if( firstPoint > secondPoint ) {
		std::swap ( firstPoint, secondPoint );
	}
	if( thirdPoint > forthPoint ) {
		std::swap ( thirdPoint, forthPoint );
	}
	return std::max( firstPoint, thirdPoint ) <= std::min( secondPoint, forthPoint );
}

int area( Coordinates firstPoint, Coordinates secondPoint, Coordinates thirdPoint )
{
	return ( secondPoint.x - firstPoint.x ) * ( thirdPoint.y - firstPoint.y )
		- ( secondPoint.y - firstPoint.y ) * ( thirdPoint.x - firstPoint.x );
}

bool Game::startLineIntersectsWithPlayer( size_t num )
{
	// Происходит проверка:
	// 1. Проекции отрезков на оси пересекаются
	// 2. Считается ориентированная площадь треугольников. Нужно, чтобы эти площади были разных знаков.
	Coordinates playersPreviousCoordinates = players[num].getPreviousPosition();
	Coordinates playersCoordinates = players[num].getPosition();
	return inBoxOnAxis( playersPreviousCoordinates.x, playersCoordinates.x, startLine.firstPoint.x, startLine.secondPoint.x )
		&& inBoxOnAxis( playersPreviousCoordinates.y, playersCoordinates.y, startLine.firstPoint.y, startLine.secondPoint.y )
		&& ( area( playersPreviousCoordinates, playersCoordinates, startLine.firstPoint )
			 * area( playersPreviousCoordinates, playersCoordinates, startLine.secondPoint ) ) <= 0
		&& ( area( startLine.firstPoint, startLine.secondPoint, playersPreviousCoordinates )
			 * area( startLine.firstPoint, startLine.secondPoint, playersCoordinates ) ) <= 0;
}

int Game::getPlayerOnFinish( bool& begining )
{
	if( begining ) { // Чтобы избавиться от ситуации, когда первый ход и все на старте (финише)
		begining = false;
		return -1;
	}
	for( size_t i = 0; i < players.size(); ++i ) {
		if( startLineIntersectsWithPlayer( i ) ) {
			return ( int ) i;
		}
	}
	return -1;
}

int Game::playerCrashedIntoCar( size_t num )
{
	for( size_t i = 0; i < players.size(); ++i ) {
		if( i != num && players[i].getPosition() == players[num].getPosition() ) {
			return ( int ) i;
		}
	}
	return -1;
}

bool Game::playerOutOfTrack( size_t num )
{
	// todo: вылетает ли траектория за пределы трассы?
	return false;
}

void Game::turnOfPlayer( size_t num )
{
	int direction = reader.readPlayersChoice( num );
	players[num].move( direction );
	int crashedPlayer = playerCrashedIntoCar( num );
	if( crashedPlayer != -1 ) {
		players[num].goToStart();
		players[crashedPlayer].goToStart();
		return;
	}
	if( playerOutOfTrack( num ) ) {
		players[num].die();
		return;
	}
}

void Game::start()
{
	std::cout << "Game has been started. Gl hf!" << std::endl;
	bool begining = true;
	int player;
	while( ( player = getPlayerOnFinish( begining ) ) == -1 ) { // -1 - никто пока к финишу не пришел
		for( size_t i = 0; i < players.size(); ++i ) {
			// todo: if (players[i].isAlive()) {
			turnOfPlayer( i );
			// }
		}
	}
	finish( player );
}

void Game::finish( size_t winner )
{
	std::cout << "Player number " << winner + 1 << " is winner! Congratulations!!!" << std::endl;
}

PointsInformation Game::getPlayersBasePoints( size_t num )
{
	return PointsInformation( true, players[num].getPreviousPosition(), players[num].getPosition() );
	// todo: вместо true
	// поставить players[num].isAlive()
}