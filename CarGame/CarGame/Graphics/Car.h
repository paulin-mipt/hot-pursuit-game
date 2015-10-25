#pragma once

#include <GL/glut.h>

#include "coord.h"

namespace Graphics {
	enum Color { Red, Blue, Green };

#define PI 3.14159265

	class Car {
	public:
		Car( std::vector<Coordinates> &coords_data, int _frames_per_step, Color _color );
		Car( std::vector<Coordinates> &coords_data );

		Car( Color _color );

		Color Get_color();

		void Push( Coordinates step );

		void Calculate_angles();

		void Draw( float cell_size, WindowCoordinates indent );

		GLuint texture;
	private:
		WindowCoordinates transate_to_wcoord( float x, float y, float cell_size, WindowCoordinates indent );
		void rotate( float &x, float &y, float angle );
		void rotate_car( float &Ax, float &Ay, float &Bx, float &By, float &Cx, float &Cy, float &Dx, float &Dy, float centerX, float centerY, float angle );
		WindowCoordinates move( float cell_size, WindowCoordinates, float &angle );

		std::vector<Coordinates> coords;
		int current_step;
		int step_iteration;
		int frames_per_step;
		Color color;
	};
}