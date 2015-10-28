﻿#pragma once

#include <vector>

#include "GlobalDefinitions.h"

namespace Core {
	class CMap {
	public:
		CMap( const CField& newMap, CLine finish, const std::vector<CCoordinates>& startPoints );

//		void print();
//		
//		// для работы с клеткой
//		void SetPosition( int x, int y );
//		void ClearPosition( int x, int y );
		bool IsEmpty( int x, int y ) const;
		
		CSize GetSize() const;
		CLine GetFinishLine() const;
		const std::vector<CCoordinates>& GetStartPoints() const;
		
	private:
		CField map;
		CSize size;
		CLine finishLine;
		std::vector<CCoordinates> startPoints;
	};
}