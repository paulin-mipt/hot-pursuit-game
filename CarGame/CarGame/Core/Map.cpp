#include <iostream>

#include "Core/Map.h"

namespace Core {
	CMap::CMap()
	{
		size.first = 0;
		size.second = 0;
	}

	CMap::CMap( const CField& newMap ) :
		map( newMap )
	{
		size.first = newMap[0].size();
		size.second = newMap.size();
	}

	CMap::~CMap()
	{}

	void CMap::print()
	{
		for( size_t i = 0; i < size.second; ++i ) {
			for( size_t j = 0; j < size.first; ++j ) {
				std::cout << map[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

	void CMap::setPosition( int x, int y )
	{
		map[y][x] = 5;
	}

	void CMap::clearPosition( int x, int y )
	{
		map[y][x] = 0;
	}

	CSize CMap::getSize()
	{
		return this->size;
	}

	bool CMap::isEmpty( int i, int j )
	{
		return (map[j][i] != 1);
	}
}