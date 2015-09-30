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