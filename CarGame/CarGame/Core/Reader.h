#pragma once

#include <vector>

#include "Core/Player.h"

namespace Core {
	typedef std::vector< std::vector<size_t> > CField;

	struct CLine {
		CLine( const CCoordinates& x, const CCoordinates& y ) :
			firstPoint( x ), secondPoint( y )
		{}

		CCoordinates firstPoint;
		CCoordinates secondPoint;
	};

	class CReader {

	public:
		CReader();

		~CReader();

		CField readMap( const std::string& path );

		CPlayersInfo readPlayers();

		int readPlayersChoice( size_t num );

		CLine readLine();
	};
}