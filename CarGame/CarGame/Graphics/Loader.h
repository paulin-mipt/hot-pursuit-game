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
		CLoader( std::string map_file, std::string cars_file, int argc, char* argv[] ); // конструктор с указанным входным файлом

	private:
		CMap read_map( std::ifstream & input );
		std::vector<CCar> read_cars( std::ifstream & input );

		CDrawing drawing_module;
		std::map< std::string, Color > color_dict;
	};
}