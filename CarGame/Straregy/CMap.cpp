#pragma once

#define DEFAULT_X_SIZE 14
#define DEFAULT_Y_SIZE 14

#include "CMap.hpp"
#include <stdexcept>
#include <algorithm>
#include <cmath>

Map::Map() : 
	xSize(DEFAULT_X_SIZE),
	ySize(DEFAULT_Y_SIZE),
	cells(DEFAULT_X_SIZE, std::vector< int >(DEFAULT_Y_SIZE, EMPTY_CELL))
{
	fillMapWithDefaultData();
}

Map::Map(const size_t xSize, const size_t ySize) :
	xSize(xSize),
	ySize(ySize),
	cells(xSize, std::vector< int >(ySize, EMPTY_CELL))
{
}

Map::Map(const std::vector< std::vector < int > > &inputCells,
	const std::pair< int, int > &_leftFinishPoint,
	const std::pair< int, int > &_rightFinishPoint) :
	cells(inputCells),
	leftFinishPoint(_leftFinishPoint),
	rightFinishPoint(_rightFinishPoint),
	xSize(inputCells.size()),
	ySize(inputCells[0].size())
{
}

Map::~Map() {
}

const std::pair<size_t, size_t> Map::size() const {
    return std::make_pair(this->xSize, this->ySize);
}

const size_t Map::sizeOnXaxis() const {
    return xSize;
}

const size_t Map::sizeOnYaxis() const {
    return ySize;
}

bool Map::canPlayerStayOnCell(int x, int y) const {
    if (x < 0 || y < 0 || x >= xSize || y >= ySize) {
        return false;
    }
    
    if (cells[x][y] == 0) {
        return true;
    } else {
        return false;
    }
}

bool Map::canPlayerStayOnCellLookOnOtherPlayers(int x, int y, int playerID, const std::vector< IPlayerState > &players) const {
    if (x < 0 || y < 0 || x >= xSize || y >= ySize) {
        return false;
    }
    
    for (int i = 0; i < players.size(); ++i) {
        if (i == playerID) {
            continue;
        } else {
            if (players[i].GetX() == x && players[i].GetY() == y) {
                return false;
            }
        }
    }
    
    if (cells[x][y] == 0) {
        return true;
    } else {
        return false;
    }
}

bool Map::hasBarrierOnPath(int xFirst, int yFirst, int xSecond, int ySecond) const {
	if (xFirst > xSecond) {
		std::swap(xFirst, xSecond);
		std::swap(yFirst, ySecond);
	}

	if (xFirst == xSecond) {
		for (int j = yFirst + 1; j < ySecond; ++j) {
			if (cells[xFirst][j] == FILLED_CELL) {
				return true;
			}
		}

		if (wrongFinishLineIntersection(xFirst, yFirst, xSecond, ySecond)) {
			return true;
		}

		return false;
	}

	int previousYInt = yFirst;

	for (int i = xFirst + 1; i < xSecond; ++i) {
		double currentY = ((double)(i - xFirst - 0.5)) 
			/ (xSecond - xFirst) * (ySecond - yFirst) + yFirst + 0.5;
		double intPart, fractPart;

		fractPart = modf(currentY, &intPart);
		int currentYInt = (int)intPart;

		if (fractPart < epsilon && yFirst > ySecond) {
			--currentYInt;
		}

		if (fractPart > 1 - epsilon && yFirst < ySecond) {
			++currentYInt;
		}

		for (int j = std::min(previousYInt, currentYInt);
				j <= std::max(previousYInt, currentYInt); ++j) {
			
			if (cells[i][j] == FILLED_CELL) {
				return true;
			}
		}

		previousYInt = currentYInt;

		if (fractPart < epsilon && yFirst > ySecond) {
			++previousYInt;
		}

		if (fractPart > 1 - epsilon && yFirst < ySecond) {
			--previousYInt;
		}

	}

	if (wrongFinishLineIntersection(xFirst, yFirst, xSecond, ySecond)) {
		return true;
	}

	return false;
}

void Map::fillMapWithDefaultData() {
    for (int i = 0; i < DEFAULT_X_SIZE; ++i) {
        for (int j = 0; j < DEFAULT_Y_SIZE; ++j) {
            if (i >= 10 && j >= 0 && i < 20 && j < 20) {
                cells[i][j] = 1;
            } else if(i == 15 && j < 20) {
                cells[i][j] = 1;
            } else {
                cells[i][j] = 0;
            }
        }
    }

	leftFinishPoint = std::make_pair(DEFAULT_X_SIZE - 2, DEFAULT_Y_SIZE - 1);
	rightFinishPoint = std::make_pair(DEFAULT_X_SIZE - 1, DEFAULT_Y_SIZE - 2);
}

void Map::print(const std::vector< IPlayerState > &players) const {
    for (int i = 0; i < xSize; ++i) {
        for (int j = 0; j < ySize; ++j) {
            for (int p = 0; p < players.size(); ++p) {
                if (players[p].getPosition() == std::make_pair(i, j)) {
                    std::cout << "*";
                } else {
                    std::cout << cells[i][j];
                }
            }
        }
        std::cout << std::endl;
    }
}

std::vector< int >& Map::operator[](int i) {
    if (i >= xSize) {
        throw std::out_of_range("index is out of range");
    }
    return cells[i];
}

const std::vector< int >& Map::operator[](int i)const {
	if (i >= xSize) {
		throw std::out_of_range("index is out of range");
	}
	return cells[i];
}

int Map::orientedArea(int ax, int ay, int bx, int by, int cx, int cy) const {
	return (bx - ax) * (cy - ay) - (by - ay) * (cx - ax);
}

bool Map::intersect(int a, int b, int c, int d) const {
	if (a > b) {
		std::swap(a, b);
	}

	if (c > d) {
		std::swap(c, d);
	}

	return std::max(a, c) <= std::min(b, d);
}

bool Map::intersectFinishLine(int xFirst, int yFirst, int xSecond, int ySecond) const {
	return (intersect(xFirst, xSecond, leftFinishPoint.first, rightFinishPoint.first)
		&& intersect(yFirst, ySecond, leftFinishPoint.second, rightFinishPoint.second)
		&& (orientedArea(xFirst, yFirst, xSecond, ySecond,
			leftFinishPoint.first, leftFinishPoint.second) * orientedArea(xFirst, yFirst,
				xSecond, ySecond, rightFinishPoint.first, rightFinishPoint.second) <= 0)
		&& (orientedArea(leftFinishPoint.first, leftFinishPoint.second, rightFinishPoint.first, rightFinishPoint.second,
			xFirst, yFirst) * orientedArea(leftFinishPoint.first, leftFinishPoint.second,
				rightFinishPoint.first, rightFinishPoint.second, xSecond, ySecond) <= 0));
}

bool Map::wrongFinishLineIntersection(int xFirst, int yFirst, int xSecond, int ySecond) const {
	if (intersectFinishLine(xFirst, yFirst, xSecond, ySecond)) {
		return (orientedArea(xFirst, yFirst, leftFinishPoint.first, leftFinishPoint.second,
			rightFinishPoint.first, rightFinishPoint.second) > 0);
	}

	return false;
}

const std::pair< int, int >& Map::GetLeftFinishPoint() const {
	return leftFinishPoint;
}

const std::pair< int, int >& Map::GetRightFinishPoint() const {
	return rightFinishPoint;
}
