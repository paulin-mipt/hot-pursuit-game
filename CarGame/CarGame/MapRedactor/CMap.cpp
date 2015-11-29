#include "stdafx.h"
#include "CMap.h"


CMap::CMap() : sizeX( DEFAULT_SIZE_X ), sizeY( DEFAULT_SIZE_Y ), colorsNumber( DEFAULT_COLORS_NUMBER )
{}


CMap::~CMap()
{}


const std::vector< std::vector<int> >& CMap::GetNumbers()
{
    return numbers;
}


int CMap::GetX()
{
    return sizeX;
}


int CMap::GetY()
{
    return sizeY;
}


void CMap::ClickCell( int i, int j )
{
    numbers[i][j] = ( numbers[i][j] + 1 ) % colorsNumber;
}


void CMap::ClickCell( int i, int j, BType bType )
{
    switch (bType) {
        case BNone:  ClickCell( i, j ); break;
        case BTree:  numbers[i][j] = 0; break;
        case BRoad:  numbers[i][j] = 1; break;
        case BWall:  numbers[i][j] = 2; break;
        case BStart:
          if (startLinePoints.size() < 2) {
            startLinePoints.push_back(std::array<int, 2> { i, j });
          } else {
            startLinePoints.pop_back();
            startLinePoints.push_front(std::array<int, 2> { i, j });
          }

          break;
    }
}


void CMap::LoadMapFromFile( std::ifstream& fin )
{
    fin >> sizeX >> sizeY;
    numbers.resize( sizeY );
    for( int i = 0; i < sizeY; i++ ) {
        numbers[i].resize( sizeX );
        for( int j = 0; j < sizeX; j++ ) {
            fin >> numbers[i][j];
        }
    }
}


void CMap::SaveMapToFile( std::ofstream & fout )
{
    fout << sizeX << " " << sizeY;
    fout << std::endl;

    for( int i = 0; i < sizeY; i++ ) {
        for( int j = 0; j < sizeX; j++ ) {
            switch( numbers[i][j] ) {
                case 0: fout << 1 << " "; break;
                case 1: fout << 0 << " "; break;
                case 2: fout << 2 << " "; break;
                case 3: fout << 3 << " "; break;
            }
        }
        fout << std::endl;
    }
}


void CMap::RestartMap()
{
	numbers = std::vector< std::vector<int> >( sizeY );

	int border = 1; // forest border
	int roadWidth = 3;

	if ( sizeX <= 10 || sizeY <= 10 ) {
		border = 0;
		roadWidth = 2;
	}

	const int ROAD = 1;
	const int FOREST = 0;
	const int WALL = 2;

	for ( int i = 0; i < sizeY; i++ ) {
		numbers[i].resize( sizeX ); // now forest is everywhere

		if ( i == border || i == sizeY - 1 - border ) { // FOREST-WALL-FOREST
			for ( int j = border; j < sizeX - border; j++ ) {
				numbers[i][j] = WALL;
			}
		}
		else if ( ( i > border && i < border + roadWidth + 1 ) ||
			( i > sizeY - 2 - border - roadWidth && i < sizeY - 1 - border ) ) // FOREST-WALL-ROAD-WALL-FOREST
		{
			// set walls
			numbers[i][border] = numbers[i][sizeX - 1 - border] = WALL;

			// set road
			for ( int j = border + 1; j < sizeX - 1 - border; j++ ) {
				numbers[i][j] = ROAD;
			}

		}
		else if ( i == border + roadWidth + 1 || i == sizeY - 2 - border - roadWidth ) { // FOREST-WALL-ROAD-WALL-ROAD-WALL-FOREST
																						 // set walls
			numbers[i][border] = numbers[i][sizeX - 1 - border] = WALL;

			for ( int j = border + roadWidth + 1; j < sizeX - 1 - border - roadWidth; j++ ) {
				numbers[i][j] = WALL;
			}

			// set road
			for ( int j = border + 1; j < border + roadWidth + 1; j++ ) {
				numbers[i][j] = ROAD;
			}

			for ( int j = sizeX - 1 - border - roadWidth; j < sizeX - 1 - border; j++ ) {
				numbers[i][j] = ROAD;
			}
		}
		else if ( i > border + roadWidth + 1 && i < sizeY - 2 - border - roadWidth ) { // FOREST-WALL-ROAD-WALL-FOREST-WALL-ROAD-WALL
			// set walls
			numbers[i][border] = numbers[i][sizeX - 1 - border] = WALL;
			numbers[i][border + roadWidth + 1] = numbers[i][sizeX - 2 - border - roadWidth] = WALL;

			// set road
			for ( int j = border + 1; j < border + roadWidth + 1; j++ ) {
				numbers[i][j] = ROAD;
			}

			for ( int j = sizeX - 1 - border - roadWidth; j < sizeX - 1 - border; j++ ) {
				numbers[i][j] = ROAD;
			}
		}
	}
}


void CMap::SetSize( int x, int y )
{
    sizeX = x;
    sizeY = y;
}