#include <iostream>

#include "Core/Map.h"

namespace Core {
	CMap::CMap( const CField& newMap, CLine start, CLine finish, const std::vector<CCoordinates>& _startPoints ) :
		map( newMap ),
		size( newMap[0].size(), newMap.size() ),
		startLine( start ),
		finishLine( finish ),
		startPoints( _startPoints )
	{}

	bool CMap::IsEmpty( int x, int y ) const
	{
		return map[y][x] == ROAD;
	}

	CSize CMap::GetSize() const
	{
		return size;
	}

	CField CMap::GetField() const
	{
		return map;
	}

	CLine CMap::GetStartLine() const
	{
		return startLine;
	}

	CLine CMap::GetFinishLine() const
	{
		return finishLine;
	}

	const std::vector<CCoordinates>& CMap::GetStartPoints() const
	{
		return startPoints;
	}
}