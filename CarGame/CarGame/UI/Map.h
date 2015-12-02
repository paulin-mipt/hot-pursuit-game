#pragma once
#include <vector>
#include <GL/glut.h>

#include "UI/Coord.h"
#include "GlobalDefinitions.h"

namespace UI {
	class CMap {
	public:
		CMap();
		CMap( const std::vector<std::vector<int>> &mapData );
		void Calculate();
		void Draw();
		float GetCellSize() const;
		
		CWindowCoordinates GetIndent() const;
		CSize GetSize() const;

		bool NeedToReload();

		GLuint textureBoard;
		GLuint textureRoad;
		GLuint textureWall;

		//GLuint textureActiveBoard;
		//GLuint textureActiveRoad;
		GLuint textureActiveCell;

		GLuint textureMap;

		void MarkPossibleMoves(const std::vector<Core::CCoordinates>& _possibleMoves);
		void UnMarkPossibleMoves(const std::vector<Core::CCoordinates>& _possibleMoves);
		void HighLightPossibleMoves();
	private:
		std::vector<Core::CCoordinates> possibleMoves;
		std::vector<std::vector<int>> map;
		float cellSize;
		CWindowCoordinates indent;
		bool needReload;
		
		const static int TEXTURE_COUNT = 5;

		void saveTexture();
		void reload();
	};
}