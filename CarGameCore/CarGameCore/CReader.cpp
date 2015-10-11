#include "CReader.h"

Reader::Reader()
{
}

Reader::~Reader()
{
}

bool isNumber( std::string number )
{
	for ( int i = 0; i < number.length(); ++i ) {
		if ( number[i] > '9' || number[i] < '0' ) {
			return false;
		}
	}
	return true;
}

Field Reader::readMap( const std::string& path )
{
	Field gameField;
	std::ifstream fin( path );

	if( !fin ) {
		std::string error = "Can't open file ";
		error += path;
		throw std::runtime_error( error );
	}

	std::string currentLine;

	while( std::getline( fin, currentLine ) ) {
		std::vector <size_t> line;
		currentLine += " ";
		while( currentLine.length() > 0 ) {
			size_t pos = currentLine.find( " " );
			std::string number = currentLine.substr(0, pos);
			if ( !isNumber(number) ) {
				std::string error = "Bad file with map: invalid symbol in ";
				error += number;
				throw std::runtime_error( error );
			}
			line.push_back( atoi( number.c_str() ) );
			currentLine.erase( 0, pos + 1 );
		}
		gameField.push_back( line );
	}

	return gameField;
}

Coordinates readCoordinates()
{
	int x, y;
	std::cin >> x >> y;

	return Coordinates( x, y );
}

PlayersInfo Reader::readPlayers()
{
	PlayersInfo info;
	std::cout << "Введите количество игроков:" << std::endl;
	size_t numberOfPlayers;
	std::cin >> numberOfPlayers;
	info.numberOfPlayers = numberOfPlayers;
	for( size_t i = 0; i < numberOfPlayers; ++i )
		info.positions.push_back( readCoordinates() );
	return info;
}


int Reader::readPlayersChoice( size_t num )
{
	std::cout << "Сейчас ход " << num + 1 << " игрока:" << std::endl;
	int move;
	std::cin >> move;
	return move;
}

Line Reader::readLine()
{

	std::cout << "Введите координаты стартовой линии:" << std::endl;
	Coordinates firstPoint = readCoordinates(),
		        secondPoint = readCoordinates();

	return Line( firstPoint, secondPoint );
}