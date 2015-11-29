﻿#pragma once

#include <vector>

#include "GlobalDefinitions.h"

namespace Core {
	class CMap {
	public:
		CMap() {}
		CMap( const CField& newMap, CLine finish, const std::vector<CCoordinates>& startPoints );

		bool IsEmpty( int x, int y ) const;
		
		CSize GetSize() const;
		CField GetField() const;
		CLine GetFinishLine() const;
		const std::vector<CCoordinates>& GetStartPoints() const;
		
	private:
		CField map;
		CSize size;
		CLine finishLine;
		std::vector<CCoordinates> startPoints;
	};
}