#pragma once

#include <vector>
#include <cmath>

#include <GL/glut.h>

#include "Graphics/Map.h"
#include "Graphics/Car.h"
/* OpenGL needs static functions and command line arguments for drawing*/

namespace Graphics {
	class CDrawing {
	public:
		CDrawing( CMap &map_data, std::vector<std::shared_ptr<CCar>> &_cars );
		CDrawing() {};
		void draw( int argc, char * argv[] );
		static void Load_texture( const char*, GLuint& texture );

	private:
		static void display();
		static void reshape( int width, int height );
		static void load();
		static void timer( int value );

		static CMap map;
		static std::vector<std::shared_ptr<CCar>> cars;
	};
}