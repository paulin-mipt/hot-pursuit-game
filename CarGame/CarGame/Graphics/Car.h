#pragma once

#include <GL/glut.h>

#include "coord.h"

namespace Graphics {
	enum Color { Red, Blue, Green };

#define PI 3.14159265

	class CCar {
	public:
		CCar( std::vector<CCoordinates> &coords_data, int _frames_per_step, Color _color );
		CCar( std::vector<CCoordinates> &coords_data );

		CCar( Color _color );

		Color Get_color();

		void Push( CCoordinates step );

		void Calculate_angles();

		void Draw( float cell_size, CWindowCoordinates indent );

		GLuint texture;
	private:
		CWindowCoordinates transate_to_wcoord( float x, float y, float cell_size, CWindowCoordinates indent );
		void rotate( float &x, float &y, float angle );
		void rotate_car( float &Ax, float &Ay, float &Bx, float &By, float &Cx, float &Cy, float &Dx, float &Dy, float centerX, float centerY, float angle );
		CWindowCoordinates move( float cell_size, CWindowCoordinates, float &angle );

		std::vector<CCoordinates> coords;
		int current_step;
		int step_iteration;
		int frames_per_step;
		Color color;
	};
}