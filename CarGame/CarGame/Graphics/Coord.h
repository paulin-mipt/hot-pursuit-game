#pragma once

namespace Graphics {
	// координаты в игре
	struct CCoordinates {
		int x;
		int y;
		float angle;
		float help_angle = 0.0;
	};

	// координаты в окне
	struct CWindowCoordinates {
		float x;
		float y;
		CWindowCoordinates( float _x, float _y ) :
			x( _x ),
			y( _y )
		{}
	};
}