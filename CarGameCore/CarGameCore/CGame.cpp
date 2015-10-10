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

int Game::getPlayerOnFinish()
{
	for( size_t i = 0; i < players.size(); ++i ) {
		bool begining = players[i].wasFirstStep();
		bool second = players[i].wasSecondStep();
		if( begining ) { // Чтобы избавиться от ситуации, когда траектория на первом и втором ходу пересекается со стартом
			players[i].makeFirstStep();
			continue;
		}
		if( second ) {
			players[i].makeSecondStep();
			continue;
		}
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
	while( !players[num].directionIsValid( direction, map.getSize() ) ) {
		std::cout << "Out of bounds error. Try again." << std::endl;
		direction = reader.readPlayersChoice( num );
	}

	players[num].move( direction, map.getSize() );

	int crashedPlayer = playerCrashedIntoCar( num );
	if( crashedPlayer != -1 ) {
		players[num].goToStart();
		clearPlayersState( crashedPlayer );
		players[crashedPlayer].goToStart();
		paintPlayersState( crashedPlayer );
		return;
	}
	if( playerOutOfTrack( num ) ) {
		players[num].die();
		return;
	}
}

void Game::initPlayersPositionsInMap()
{
	for( size_t i = 0; i < players.size(); ++i ) {
		Coordinates currentCoordinates = players[i].getPosition();
		map.setPosition( currentCoordinates.x, currentCoordinates.y );
	}
}

void Game::clearPlayersState( size_t num ) // Стирает изображение игрока с поля
{
	Coordinates old = players[num].getPreviousPosition();
	Coordinates now = players[num].getPosition();
	map.clearPosition( old.x, old.y );
	map.clearPosition( now.x, now.y );
}

void Game::paintPlayersState( size_t num ) // Рисует изображение игрока на поле
{
	Coordinates previousCoordinates = players[num].getPreviousPosition();
	Coordinates currentCoordinates = players[num].getPosition();
	map.setPosition( previousCoordinates.x, previousCoordinates.y );
	map.setPosition( currentCoordinates.x, currentCoordinates.y );
}

void Game::start()
{
	std::cout << "Game has been started. Gl hf!" << std::endl;
	int player;
	initPlayersPositionsInMap(); // На карте проставляются координаты машинок
	while( ( player = getPlayerOnFinish() ) == -1 ) { // -1 - никто пока к финишу не пришел
		for( size_t i = 0; i < players.size(); ++i ) {
			// todo: if (players[i].isAlive()) {
			clearPlayersState( i );
			turnOfPlayer( i ); // AI: Если будет AI, здесь он запускается (перед этим, занести его в players[])
			paintPlayersState( i );
			map.print();  // Вывод поля на консоль
			// }
		}
	}
	finish( player );
}

void Game::finish( size_t winner )
{
	std::cout << "Player number " << winner + 1 << " is winner! Congratulations!!!" << std::endl;
}

PointsInformation Game::getPlayersBasePoints( size_t num )  // Frontend: Для Frontend'a - получение точек для отрисовки
{
	num = 10050;
	if( num < 0 || num >= players.size() ) {
		std::string error = "Game::getPlayersBasePoints: ";
		if( num < 0 ) {
			error += "num < 0";
		} else {
			error += "num > number of players";
		}
		throw std::invalid_argument( error );
	}
	return PointsInformation( true, players[num].getPreviousPosition(), players[num].getPosition() );
	// todo: вместо true
	// поставить players[num].isAlive()
}