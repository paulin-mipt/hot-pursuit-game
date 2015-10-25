#include "Graphics/Map.h"

namespace Graphics {
	Map::Map() :
		texture_board( 0 ),
		texture_road( 0 ),
		texture_map( 0 ),
		cell_size( 0 ),
		indent( 0, 0 ),
		need_reload( 0 )
	{}

	Map::Map( const std::vector<std::vector<int>>& map_data ) :
		texture_board( 0 ),
		texture_road( 0 ),
		texture_map( 0 ),
		map( map_data ),
		cell_size( 0 ),
		indent( 0, 0 ),
		need_reload( 0 )
	{
		glGenTextures( 1, &texture_map );
		glGenTextures( 1, &texture_board );
		glGenTextures( 1, &texture_road );
		need_reload = true;
	}

	void Map::Calculate()
	{
		int n = map.size(), m = map[0].size();
		float height = glutGet( GLUT_WINDOW_HEIGHT ),
			width = glutGet( GLUT_WINDOW_WIDTH );
		cell_size = fmin( height / n, width / m ); // the length of one little square - "cell"
		indent.x = (width - cell_size * m) / 2; // indent from left and right window sides
		indent.y = (height - cell_size * n) / 2;  // indent from top and bottom window sides
		need_reload = true; // need to reload map
	}

	void Map::save_texture()
	{
		// write window to array of pixels
		unsigned long imageSize;
		GLint viewPort[4];
		glGetIntegerv( GL_VIEWPORT, viewPort );
		GLint width = viewPort[2];
		GLint height = viewPort[3];
		imageSize = ((width + ((4 - (width % 4)) % 4))*height * 3);
		std::shared_ptr<GLbyte> data = std::shared_ptr<GLbyte>( new GLbyte[imageSize] );
		glReadBuffer( GL_FRONT );
		glReadPixels( 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data.get() );

		// write pixels to texture of map
		glBindTexture( GL_TEXTURE_2D, texture_map );
		gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data.get() );
		glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
			float( GL_MODULATE) );
	}

	void Map::reload()
	{
		int n = map.size(), m = map[0].size();
		for( int i = 0; i < n; i++ ) {
			for( int j = 0; j < m; j++ ) {
				glEnable( GL_TEXTURE_2D );
				if( map[i][j] == 1 ) {
					glBindTexture( GL_TEXTURE_2D, texture_board ); // load a texture of board (forest)
				} else {
					glBindTexture( GL_TEXTURE_2D, texture_road ); // load a texture of road
				}
				//calculate coordinates
				float left = j * cell_size + indent.x;
				float right = (j + 1) * cell_size + indent.x;
				float bottom = i * cell_size + indent.y;
				float top = (i + 1) * cell_size + indent.y;
				//draw a cell with texture (board or road)
				glBegin( GL_POLYGON );
				glTexCoord2f( 0.0f, 0.0f ); glVertex3f( left, bottom, 0.0f );
				glTexCoord2f( 1.0f, 0.0f ); glVertex3f( right, bottom, 0.0f );
				glTexCoord2f( 1.0f, 1.0f ); glVertex3f( right, top, 0.0f );
				glTexCoord2f( 0.0f, 1.0f ); glVertex3f( left, top, 0.0f );
				glEnd();
			}
		}
		glutSwapBuffers();
		save_texture(); // save the whole window with map to texture
		need_reload = false;
	}

	void Map::Draw()
	{
		if( need_reload ) {
			reload();
			return;
		}
		// load window from texture
		glEnable( GL_TEXTURE_2D );
		int height = glutGet( GLUT_WINDOW_HEIGHT ),
			width = glutGet( GLUT_WINDOW_WIDTH );
		// choose texture
		glBindTexture( GL_TEXTURE_2D, texture_map );
		// draw a polygon of window size with texture
		glBegin( GL_POLYGON );
		glTexCoord2f( 0.0f, 0.0f ); glVertex3f( 0, 0, 0.0f );
		glTexCoord2f( 1.0f, 0.0f ); glVertex3f( width, 0, 0.0f );
		glTexCoord2f( 1.0f, 1.0f ); glVertex3f( width, height, 0.0f );
		glTexCoord2f( 0.0f, 1.0f ); glVertex3f( 0, height, 0.0f );
		glEnd();

	}

	float Map::Get_cell_size()
	{
		return cell_size;
	}

	WindowCoordinates Map::Get_indent()
	{
		return indent;
	}

	bool Map::Need_to_reload()
	{
		return need_reload;
	}
}