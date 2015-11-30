#pragma once

#include <vector>

#include "GlobalDefinitions.h"

namespace Core {
	class CMap {
	public:
		CMap() {}
		CMap( const CField& newMap, CLine start, CLine finish, const std::vector<CCoordinates>& _startPoints );

		bool IsEmpty( int x, int y ) const;
		
		CSize GetSize() const;
		CField GetField() const;
		CLine GetStartLine() const;
		CLine GetFinishLine() const;
//		int GetMaxNumberOfPlayers() const;

		const std::vector<CCoordinates>& GetStartPoints() const;
		
	private:
		CField map;
		CSize size;
		CLine startLine;
		CLine finishLine;
//		int maxNumberOfPlayers;
		std::vector<CCoordinates> startPoints;
	};
}