#include "CReader.h"

Reader::Reader()
{
}

Reader::~Reader()
{
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
			line.push_back( atoi( currentLine.substr( 0, pos ).c_str() ) );
			currentLine.erase( 0, pos + 1 );
		}
		gameField.push_back( line );
	}

	std::cout << gameField.size() << " " << gameField[0].size() << std::endl;

	return gameField;
}

Coordinates readCoordinates()
{
	int x, y;
	std::cin >> x >> y;

	return Coordinates( x - 1, y - 1 );
}

PlayersInfo Reader::readPlayers()
{
	PlayersInfo info;
	std::cout << "Enter number of players:" << std::endl;
	size_t number_of_players;
	std::cin >> number_of_players;
	info.numberOfPlayers = number_of_players;
	for( size_t i = 0; i < number_of_players; ++i )
		info.positions.push_back( readCoordinates() );
	return info;
}


int Reader::readPlayersChoice( size_t num )
{
	std::cout << "Now " << num + 1 << " player:" << std::endl;
	int move;
	std::cin >> move;
	return move;
}

Line Reader::readLine()
{

	std::cout << "Enter coordinates of startline:" << std::endl;
	Coordinates first_point = readCoordinates(),
		second_point = readCoordinates();

	return Line( first_point, second_point );
}