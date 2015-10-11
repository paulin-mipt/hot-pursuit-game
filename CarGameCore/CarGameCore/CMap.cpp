#include "CMap.h"

Map::Map()
{
}

Map::Map( const Field& newMap ) :
	map( newMap )
{
	size.first = newMap[0].size();
	size.second = newMap.size();
}

Map::~Map()
{
}

bool Map::isEmpty(int i, int j) {
	return ( map[i][j] == 0 );
}