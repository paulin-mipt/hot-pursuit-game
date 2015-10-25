#pragma once
#include <vector>
#include <memory>
#include <GL/glut.h>
#include <SOIL/SOIL.h>

#include "Graphics/Coord.h"

namespace Graphics {
	class CMap {
	public:
		CMap();
		CMap( const std::vector<std::vector<int>> &map_data );
		void Calculate();
		void Draw();
		float Get_cell_size();
		CWindowCoordinates Get_indent();

		bool Need_to_reload();

		GLuint texture_board;
		GLuint texture_road;
		GLuint texture_map;
	private:
		std::vector<std::vector<int>> map; // TODO может тут хранить не в виде 2мерного массива?
		float cell_size;
		CWindowCoordinates indent;
		bool need_reload;

		void save_texture();
		void reload();
	};
}