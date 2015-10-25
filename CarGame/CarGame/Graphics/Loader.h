#pragma once
#include <string>
#include <vector>
#include <map>
#include <fstream>

#include "Graphics/Drawing.h"
#include "Graphics/Car.h"
#include "Graphics/Coord.h"
#include "Graphics/Map.h"

namespace Graphics {
	const int DEFAULT_WINDOW_WIDTH = 500;
	const int DEFAULT_WINDOW_HEIGHT = 500;
	const int DEFAULT_STEPS_PER_CELL = 20;

	class CLoader {
	public:
		CLoader( const std::string& map_file, const std::string& cars_file, CMap& map, std::vector<CCar>& cars );

	private:
		CMap read_map( std::istream & input );
		std::vector<CCar> read_cars( std::istream & input );

		std::map< std::string, Color > color_dict;
	};
}