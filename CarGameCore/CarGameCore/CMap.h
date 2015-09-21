#pragma once

#include <vector>

typedef std::vector< std::vector<size_t> > Field;

class Map {
public:
	Map();

	Map( const Field& newMap );

	~Map();

private:
	Field map; // Table, in which cells are: 0-free cell, 1-non-free cell
};