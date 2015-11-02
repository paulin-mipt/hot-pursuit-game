#pragma once

#include <utility>
#include <vector>
#include <memory>
#include "IPlayerState.h"

class IMap {
public:
	virtual const std::pair<size_t, size_t> size() const = 0; // returs xSize, ySize pair
	virtual const size_t sizeOnXaxis() const = 0;             // returs xSize
	virtual const size_t sizeOnYaxis() const = 0;             // returs ySize

	virtual std::vector< int > &operator[](int i) = 0;

	virtual bool canPlayerStayOnCell(int x, int y) const = 0;
	virtual bool hasBarrierOnPath(int xFirst, int yFirst, int xSecond, int ySecond) const = 0;
	virtual bool canPlayerStayOnCellLookOnOtherPlayers(int x, int y, int playerID,
		std::shared_ptr< std::vector< IPlayerState > > players) const = 0;

	virtual const std::shared_ptr< std::vector< std::pair< int, int > > > GetFinishPoints() const = 0;

	// methods for testing
	// only for default size map!
	virtual void fillMapWithTestData() = 0;
	virtual void fillMapWithTestData2() = 0;

	virtual void initializationMap( std::vector< std::vector< size_t > > map );
	virtual void setFinishLine( int startX, int startY, int finishX, int finishY );

	virtual void print(std::shared_ptr< std::vector< IPlayerState > > players) = 0;
};