#include <iostream>

#include "Core/Map.h"

namespace Core {
	CMap::CMap( const CField& newMap, CLine finish, const std::vector<CCoordinates>& _startPoints ) :
		map( newMap ),
		size( newMap[0].size(), newMap.size() ),
		finishLine( finish ),
		startPoints( _startPoints )
	{}

//	void CMap::print()
//	{
//		for( size_t i = 0; i < size.second; ++i ) {
//			for( size_t j = 0; j < size.first; ++j ) {
//				std::cout << map[i][j] << " ";
//			}
//			std::cout << std::endl;
//		}
//	}
//	
//	void CMap::SetPosition( int x, int y )
//	{
//		map[y][x] = CAR;
//	}
//
//	void CMap::ClearPosition( int x, int y )
//	{
//		map[y][x] = ROAD;
//	}

	bool CMap::IsEmpty( int x, int y ) const
	{
		return map[y][x] != FOREST;
	}

	CSize CMap::GetSize() const
	{
		return this->size;
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