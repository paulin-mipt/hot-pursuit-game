#include "CMap.h"

Map::Map()
{
}

Map::Map( const Field& newMap ) :
	map( newMap )
{
	size.first = 0; // todo: set size of map
	size.second = 0;
}

Map::~Map()
{
}