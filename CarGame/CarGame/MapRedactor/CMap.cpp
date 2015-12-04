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
        case BTree:  numbers[i][j] = 1; break;
        case BRoad:  numbers[i][j] = 0; break;
        case BWall:  numbers[i][j] = 2; break;
        case BStart:
          if (startLinePoints.size() < 2) {
              startLinePoints.push_front(std::array<int, 2> { i, j });
          } else {
              startLinePoints.pop_back();
              startLinePoints.push_front(std::array<int, 2> { i, j });
          }

          // запретить негоризонтальные и пустые стартовые линии
          if (startLinePoints.size() == 2) {
              // негоризонтальные
              if (startLinePoints.front()[0] != startLinePoints.back()[0])
                  startLinePoints.pop_back();
              // вырожденные
              else if (startLinePoints.front()[1] == startLinePoints.back()[1])
                  startLinePoints.pop_back();
          }
          break;
        case BFinish:
          if (finishLinePoints.size() < 2) {
            finishLinePoints.push_front(std::array<int, 2> { i, j });
          } else {
            finishLinePoints.pop_back();
            finishLinePoints.push_front(std::array<int, 2> { i, j });
          }

          // запретить негоризонтальные и пустые финишные линии
          if (finishLinePoints.size() == 2) {
            // негоризонтальные
            if (finishLinePoints.front()[0] != finishLinePoints.back()[0])
              finishLinePoints.pop_back();
            // вырожденные
            else if (finishLinePoints.front()[1] == finishLinePoints.back()[1])
              finishLinePoints.pop_back();
          }
          break;
    }
}


void CMap::LoadMapFromFile( std::ifstream& fin )
{
    fin >> sizeY >> sizeX;
    numbers.resize( sizeY );
    for( int i = 0; i < sizeY; i++ ) {
        numbers[i].resize( sizeX );
        for( int j = 0; j < sizeX; j++ ) {
            fin >> numbers[i][j];
        }
    }

    startLinePoints.resize(0);
    std::array<int, 2> point;
    fin >> point[0] >> point[1];
    startLinePoints.push_back(point);
    fin >> point[0] >> point[1];
    startLinePoints.push_back(point);

    finishLinePoints.resize(0);
    fin >> point[0] >> point[1];
    finishLinePoints.push_back(point);
    fin >> point[0] >> point[1];
    finishLinePoints.push_back(point);
}


void CMap::SaveMapToFile( std::ofstream & fout )
{
    fout << sizeY << " " << sizeX;
    fout << std::endl;

    for( int i = 0; i < sizeY; i++ ) {
        for( int j = 0; j < sizeX; j++ ) {
             fout << numbers[i][j] << " ";
        }
        fout << std::endl;
    }

    std::list<std::array<int, 2>> points = StartLinePoints();
    fout << points.front()[0] << " " << points.front()[1] << " ";
    points.pop_front();
    fout << points.front()[0] << " " << points.front()[1] << std::endl;
     
    points = FinishLinePoints();
    fout << points.front()[0] << " " << points.front()[1] << " ";
    points.pop_front();
    fout << points.front()[0] << " " << points.front()[1] << std::endl;
}


void CMap::RestartMap()
{
  startLinePoints.clear(); 
  finishLinePoints.clear();
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