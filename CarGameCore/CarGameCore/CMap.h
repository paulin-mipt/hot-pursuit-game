#pragma once

#include <vector>

typedef std::vector< std::vector<size_t> > Field;

class Map {
public:
	Map();

	Map( const Field& newMap );

	~Map();

private:
	Field map; // Таблица, элементы котрой 1/0. 1 - препятствие, 0 - свободная клетка
};