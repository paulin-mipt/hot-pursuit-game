#include <fstream>
#include <exception>
#include <vector>

#include "Core/Reader.h"
#include "Core/Map.h"
#include "GlobalDefinitions.h"

namespace Core {
	CMap CReader::ReadMap( const LPWSTR path )
	{
		CField gameField;
		std::vector<CCoordinates> startPoints;

		std::ifstream in( path );
		if( !in ) {
			throw std::runtime_error( std::string( "Can't open file" ) );
		}

		int n, m;
		in >> n >> m;
		for( int i = 0; i < n; ++i ) {
			gameField.push_back( std::vector<Cell>() );
			for( int j = 0; j < m; ++j ) {
				int cellCode;
				in >> cellCode;
				Cell cell = Cell(cellCode);
				switch ( cell ) {
					case ROAD:
					case FOREST:
					case WALL:
						gameField[i].push_back( cell );
						break;
					//case CAR:
					//	gameField[i].push_back( ROAD );
					//	startPoints.push_back( CCoordinates( j, i ) );
					//	break;
					default:
						throw std::invalid_argument( std::string( "invalid cell type on column " ) + std::to_string( i ) + " row " + std::to_string( j ) );
				}
			}
		}
		int x1, y1, x2, y2;
		in >> x1 >> y1 >> x2 >> y2;
		CLine startLine = CLine( CCoordinates( x1, y1 ), CCoordinates( x2, y2 ) );
		for( int i = x1; i <= x2; i++ ) {
			for( int j = y1; j <= y2; j++ ) {
				if( gameField[i][j] == ROAD ) {
					startPoints.push_back( CCoordinates( i, j ) );
				}
			}
		}

		in >> x1 >> y1 >> x2 >> y2;
		CLine finishLine = CLine( CCoordinates( x1, y1 ), CCoordinates( x2, y2 ) );

		return CMap( gameField, startLine, finishLine, startPoints );
	}
}