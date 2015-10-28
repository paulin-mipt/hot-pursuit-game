#include <fstream>
#include <exception>
#include <string>

#include "Core/Reader.h"
#include "Core/Map.h"

namespace Core {
//	bool isNumber( std::string number )
//	{
//		for( int i = 0; i < number.length(); ++i ) {
//			if( number[i] > '9' || number[i] < '0' ) {
//				return false;
//			}
//		}
//		return true;
//	}

	CMap CReader::ReadMap( const std::string& path )
	{
		CField gameField;
		std::vector<CCoordinates> startPoints;

		std::ifstream in( path );
		if( !in ) {
			throw std::runtime_error( std::string( "Can't open file " ) + path );
		}

		int n, m;
		in >> n >> m;
		for( int i = 0; i < n; ++i ) {
			gameField.push_back( std::vector<Cell>( 0 ) );
			for( int j = 0; j < m; ++j ) {
				int cellCode;
				in >> cellCode;
				Cell cell = Cell(cellCode);
				switch ( cell ) {
					case ROAD:
					case FOREST:
						gameField[i].push_back( cell );
						break;
					case CAR:
						gameField[i].push_back( ROAD );
						startPoints.push_back( CCoordinates( j, i ) );
						break;
					default:
						throw std::invalid_argument( std::string( "invalid cell type on column " ) + std::to_string( i ) + " row " + std::to_string( j ) );
				}
			}
		}
		int x1, y1, x2, y2;
		in >> x1 >> y1 >> x2 >> y2;
		CLine finishLine = CLine( CCoordinates( x1, y1 ), CCoordinates( x2, y2 ) );

		return CMap( gameField, finishLine, startPoints );
//		std::string currentLine;
//
//		while( std::getline( in, currentLine ) ) {
//			std::vector<Cell> row;
//			currentLine += " ";
//			while( currentLine.length() > 0 ) {
//				size_t pos = currentLine.find( " " );
//				std::string number = currentLine.substr( 0, pos );
//				if( !isNumber( number ) ) {
//					throw std::runtime_error( std::string( "Bad file with map: invalid symbol in " ) + number );
//				}
//				row.push_back( Cell( std::atoi( number.c_str() ) ) );
//				currentLine.erase( 0, pos + 1 );
//			}
//			gameField.push_back( row );
//		}
	}

//	CCoordinates readCoordinates( std::istream& in )
//	{
//		int x, y;
//		in >> x >> y;
//		if( x <= 0 || y <= 0 ) {
//			std::string error = "Bad input: invalid coordinates";
//			throw std::runtime_error( error );
//		}
//		return CCoordinates( x - 1, y - 1 );
//	}
//
//	CPlayersInfo CReader::ReadPlayers( const std::string& path )
//	{
//		CPlayersInfo info;
//
//		std::ifstream in( path );
//		if( !in ) {
//			throw std::runtime_error( std::string( "Can't open file " ) + path );
//		}
//
//		int numberOfPlayers;
//		in >> numberOfPlayers;
//		if( numberOfPlayers <= 0 ) {
//			std::string error = "Bad input: invalid number of players";
//			throw std::runtime_error( error );
//		}
//		info.numberOfPlayers = numberOfPlayers;
//		for( int i = 0; i < numberOfPlayers; ++i )
//			info.positions.push_back( readCoordinates(in) );
//		return info;
//	}
//
//	int CReader::ReadPlayersChoice( size_t num )
//	{
//		std::cout << "Now " << num + 1 << " player:" << std::endl;
//		int move;
//		std::cin >> move;
//		if( move < 1 || move > 9 ) {
//			std::string error = "Bad input: invalid move";
//			throw std::runtime_error( error );
//		}
//		return move;
//	}
}