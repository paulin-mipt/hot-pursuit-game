#include "CGame.h"

Game::Game()
{
}

Game::Game( const Map& newMap, const PlayersInfo& newPlayersInfo, const Reader& newReader ) :
	map( newMap ), reader( newReader )
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

bool Game::playersOnFinish()
{
	// 2 точки - прямая старта.
	// Требуется проверить, пересекается ли она с траекторией машины.

	return false;
}

void Game::turnOfPlayer( size_t number )
{
	// Игра
}

void Game::start()
{
	std::cout << "Game has been started. Gl hf!" << std::endl;
	/*while( !playersOnFinish() ) {
		for( size_t i = 0; i < players.size(); ++i ) {
			turnOfPlayer( i );
		}
	}*/
}