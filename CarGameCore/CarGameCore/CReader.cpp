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

	if (!fin)
	{
		std::string error = "Can't open file ";
		error += path;
		throw std::runtime_error( error );
	}

	std::string currentLine;

	while ( std::getline(fin, currentLine) )
	{
		std::vector <size_t> line;
		currentLine += " ";
		while (currentLine.length() > 0)
		{
			size_t pos = currentLine.find( " " );
			line.push_back( atoi( currentLine.substr( 0, pos ).c_str() ) );
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

	return Coordinates(x, y);
}

PlayersInfo Reader::readPlayers()
{
	PlayersInfo info;
	info.positions.push_back(readCoordinates());
	return info;
}


Coordinates Reader::readPlayersChoice()
{
	return readCoordinates();
}
