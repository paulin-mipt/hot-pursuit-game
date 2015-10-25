#include <fstream>
#include <iostream>
#include <exception>
#include <string>
#include <assert.h>

#include "Core/Reader.h"

namespace Core {
	CReader::CReader()
	{}

	CReader::~CReader()
	{}

	bool isNumber( std::string number )
	{
		for( int i = 0; i < number.length(); ++i ) {
			if( number[i] > '9' || number[i] < '0' ) {
				return false;
			}
		}
		return true;
	}

	CField CReader::readMap( const std::string& path )
	{
		CField gameField;
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
				std::string number = currentLine.substr( 0, pos );
				if( !isNumber( number ) ) {
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

	CCoordinates readCoordinates()
	{
		int x, y;
		std::cin >> x >> y;
		if( x <= 0 || y <= 0 ) {
			std::string error = "Bad input: invalid coordinates";
			throw std::runtime_error( error );
		}
		return CCoordinates( x - 1, y - 1 );
	}

	CPlayersInfo CReader::readPlayers()
	{
		CPlayersInfo info;
		std::cout << "Enter number of players:" << std::endl;
		int numberOfPlayers;
		std::cin >> numberOfPlayers;
		if( numberOfPlayers <= 0 ) {
			std::string error = "Bad input: invalid number of players";
			throw std::runtime_error( error );
		}
		info.numberOfPlayers = numberOfPlayers;
		for( int i = 0; i < numberOfPlayers; ++i )
			info.positions.push_back( readCoordinates() );
		return info;
	}

	int CReader::readPlayersChoice( size_t num )
	{
		std::cout << "Now " << num + 1 << " player:" << std::endl;
		int move;
		std::cin >> move;
		if( move < 1 || move > 9 ) {
			std::string error = "Bad input: invalid move";
			throw std::runtime_error( error );
		}
		return move;
	}

	CLine CReader::readLine()
	{
		std::cout << "Enter coordinates of startline:" << std::endl;
		CCoordinates firstPoint = readCoordinates(),
			secondPoint = readCoordinates();

		return CLine( firstPoint, secondPoint );
	}
}