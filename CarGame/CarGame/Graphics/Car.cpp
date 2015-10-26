﻿#include <vector>

#include "Graphics/Car.h"

namespace Graphics {
	CCar::CCar( const CCoordinates& coords_data, int _frames_per_step, Color _color = Red ) :
		coords( coords_data ),
		current_step( 0 ),
		step_iteration( 0 ),
		frames_per_step( _frames_per_step ),
		color( _color )
	{}

	CCar::CCar( const CCoordinates& coords_data )
	{
		coords = coords_data;
		color = Red;
	}

	CCar::CCar( Color _color )
	{
		color = _color;
		frames_per_step = 200;
		current_step = 0;
		step_iteration = 0;
	}

	Color CCar::Get_color()
	{
		return color;
	}

//	void CCar::Push( CCoordinates step )
//	{
//		coords.push_back( step );
//	}

	void CCar::rotate( float &x, float &y, float angle )
	{
		float tx = x,
			ty = y;
		x = tx * cos( angle ) - ty * sin( angle );
		y = tx * sin( angle ) + ty * cos( angle );
	}

	void CCar::rotate_car( float &Ax, float &Ay, float &Bx, float &By, float &Cx, float &Cy, float &Dx, float &Dy, float centerX, float centerY, float angle )
	{
		Ax -= centerX;
		Bx -= centerX;
		Cx -= centerX;
		Dx -= centerX;

		Ay -= centerY;
		By -= centerY;
		Cy -= centerY;
		Dy -= centerY;

		rotate( Ax, Ay, angle );
		rotate( Bx, By, angle );
		rotate( Cx, Cy, angle );
		rotate( Dx, Dy, angle );

		Ax += centerX;
		Bx += centerX;
		Cx += centerX;
		Dx += centerX;

		Ay += centerY;
		By += centerY;
		Cy += centerY;
		Dy += centerY;
	}


	void CCar::Draw( float cell_size, CWindowCoordinates indent )
	{
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, texture );
		glTexEnvf( GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE );
		float angle = 0.0;
		CWindowCoordinates cord = move( cell_size, indent, angle );
		float left = cord.x;
		float right = cord.x + cell_size;
		float bottom = cord.y + cell_size / 2;
		float top = cord.y;
		glDepthMask( GL_FALSE );
		glEnable( GL_BLEND );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
		glBegin( GL_POLYGON );
		float Ax = left,
			Ay = bottom,
			Bx = right,
			By = bottom,
			Cx = right,
			Cy = top,
			Dx = left,
			Dy = top;

		float centerX = Dx - (Dx - Bx) / 2,
			centerY = Dy - (Dy - By) / 2;
		rotate_car( Ax, Ay, Bx, By, Cx, Cy, Dx, Dy, centerX, centerY, angle );
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f( Ax, Ay, 0.0f );
		glTexCoord2f( 1.0f, 0.0f ); glVertex3f( Bx, By, 0.0f );
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f( Cx, Cy, 0.0f );
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f( Dx, Dy, 0.0f );
		glEnd();
		glDisable( GL_BLEND );
		glDepthMask( GL_TRUE );
	}

	CWindowCoordinates CCar::move( float cell_size, CWindowCoordinates indent, float &angle )
	{
		throw std::runtime_error( "CCar::move not implemented" );
//		if( current_step + 1 < coords.size() ) {
//			if( step_iteration < frames_per_step ) {
//				step_iteration++;
//			} else {
//				current_step++;
//				step_iteration = 0;
//			}
//		}
//
//		if( current_step + 1 < coords.size() ) {
//			float coord_x = coords[current_step + 1].x - coords[current_step].x;
//			float coord_y = coords[current_step + 1].y - coords[current_step].y;
//			float dx = (coord_x) / frames_per_step;
//			float dy = (coord_y) / frames_per_step;
//			float x = coords[current_step].x + step_iteration * dx;
//			float y = coords[current_step].y + step_iteration * dy;
//
//			angle = abs( 2.0*coords[current_step].help_angle - coords[current_step].angle );
//			return transate_to_wcoord( x, y, cell_size, indent );
//		} else {
//			CCoordinates last = coords.back();
//			return transate_to_wcoord( last.x, last.y, cell_size, indent );
//		}
		return CWindowCoordinates( 0, 0 );
	}

	float find_angle( int x, int y )
	{
		float angle = 0.0;
		int length = x * x + y * y;
		if( length != 0 ) {
			angle = float(x) / sqrt( length );
		}
		return acos( angle );
	}

	void CCar::Calculate_angles()
	{
		throw std::runtime_error( "CCar::Calculate_angles not implemented" );
//		for( int i = 1; i < coords.size(); ++i ) {
//			coords[i - 1].angle = find_angle( coords[i].x - coords[i - 1].x, coords[i].y - coords[i - 1].y );
//			if( coords[i].y - coords[i - 1].y < 0 ) {
//				coords[i - 1].help_angle = PI;
//			}
//		}
//		coords[coords.size() - 1].angle = coords[coords.size() - 2].angle;
//		coords[coords.size() - 1].help_angle = coords[coords.size() - 2].help_angle;
	}

	// TODO добавить умножение на коэфициент сжатия чтобы соответствовать 2.5D
	CWindowCoordinates CCar::transate_to_wcoord( float x, float y, float cell_size, CWindowCoordinates indent )
	{
		CWindowCoordinates wcoord( 0, 0 );
		wcoord.x = x * cell_size + indent.x;
		wcoord.y = y * cell_size + indent.y;
		return wcoord;
	}
}