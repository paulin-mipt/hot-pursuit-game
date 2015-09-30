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

bool startLineIntersectsWithPlayer( size_t num )
{
	// Дано: startLine и players[num].
	// Требуется проверить, пересекается ли она с траекторией игрока.
	return false;
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

void Game::turnOfPlayer( size_t number )
{
	// Ход игрока + проверка, что остался на треке
}

void Game::start()
{
	std::cout << "Game has been started. Gl hf!" << std::endl;
	bool begining = true;
	int player;
	while( ( player = getPlayerOnFinish( begining ) ) == -1 ) { // -1 - никто пока к финишу не пришел
		for( size_t i = 0; i < players.size(); ++i ) {
			turnOfPlayer( i );
		}
	}
	finish( player );
}

void Game::finish( size_t winner )
{
	std::cout << "Player number " << winner + 1 << " is winner! Congratulations!!!" << std::endl;
}