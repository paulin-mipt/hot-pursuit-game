#pragma once

#include <vector>

typedef std::pair<size_t, size_t> Size;
typedef std::vector< std::vector<size_t> > Field;

class Map {
public:
	Map();

	Map( const Field& newMap );

	~Map();

private:
	Field map; // Карта (таблица), в которой 1 - препятствие (дороги нет). А 0 - дорога.
	Size size;
};