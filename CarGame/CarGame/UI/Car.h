#pragma once

#include <GL/glut.h>

#include "UI/Coord.h"
#include "GlobalDefinitions.h"

namespace UI {
	enum Color { RED, GREEN, BLUE, ORANGE };

#define PI 3.14159265

	class CCar {
	public:
		CCar( CCoordinates startCoordinates, Color carColor );

		Color GetColor() const;
		CCoordinates GetCoordinates() const;

		void Draw( float cellSize, CWindowCoordinates indent, CSize mapSize );

		void Move( CCoordinates coordinates );
		void Crash();
		void SetOpacity( float opacity );

		GLuint texture;
	private:
		CWindowCoordinates transateToWcoord( float x, float y, float cellSize, CWindowCoordinates indent, CSize mapSize ) const;
		void rotate( float &x, float &y, float angle ) const;
		void rotateCar( float &Ax, float &Ay, float &Bx, float &By, float &Cx, float &Cy, float &Dx, float &Dy, float centerX, float centerY, float angle ) const;
//		CWindowCoordinates move( float cellSize, CWindowCoordinates, float &angle );

		CCoordinates coords;
//		int current_step;
//		int stepIteration;
//		int framesPerStep;
		Color color;
		float alpha;
		bool crashed;
	};
}