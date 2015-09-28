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

	if (fin == NULL)
	{
		std::string error = "Can't open file ";
		error += path;
		throw std::runtime_error( error );
	}

	std::string currentLine;
	std::vector <size_t> line;

	while ( !std::getline(fin, currentLine) )
	{
		currentLine += " ";
		while (currentLine.length() > 0)
		{
			size_t pos = currentLine.find( " " );
			line.push_back( atoi( currentLine.substr( pos ).c_str() ) );
		}
		gameField.push_back( line );
	}

	return gameField;
}

PlayersInfo Reader::readPlayers()
{
	PlayersInfo info;
	// Чтение с консоли
	return info;
}


Coordinates Reader::readPlayersChoice()
{
	
	return Coordinates( 0, 0 );
}
