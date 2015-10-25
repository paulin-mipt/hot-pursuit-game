#pragma once

namespace Graphics {
	// координаты в игре
	struct Coordinates {
		int x;
		int y;
		float angle;
		float help_angle = 0.0;
	};

	// координаты в окне
	struct WindowCoordinates {
		float x;
		float y;
		WindowCoordinates( float _x, float _y ) :
			x( _x ),
			y( _y )
		{}
	};
}