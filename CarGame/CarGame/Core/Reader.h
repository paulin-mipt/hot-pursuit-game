#pragma once

#include <vector>

#include "GlobalDefinitions.h"

namespace Core {
	class CMap;

	class CReader {
	public:
		CMap ReadMap( const std::string& path );

//		CPlayersInfo ReadPlayers( const std::string & path );
//
//		int ReadPlayersChoice( size_t num );
	};
}