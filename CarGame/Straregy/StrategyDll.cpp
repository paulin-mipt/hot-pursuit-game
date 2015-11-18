#pragma once
#include "StrategyDll.h"
#include "IPlayerState.h"
#include "IMap.h"
#include "CPlayerState.hpp"
#include "CMap.hpp"
#include "CAStarStrategyOnYAGSBPL.hpp"
#include <time.h>

Map PutPlayersOnMap(const Map &_map, const std::vector< std::shared_ptr<IPlayerState> > &_playerStateList, int CurrentPlayerIndex) {
	int xSize = _map.size().first;
	int ySize = _map.size().second;
	Map res(xSize, ySize);
	for (int x = 0; x < xSize; ++x)
		for (int y = 0; y < ySize; ++y)
		{
			int cellValue = _map[x][y];
			if (cellValue == 0)
			{
				for (int p = 0; p < _playerStateList.size(); ++p)
				{
					if (p == CurrentPlayerIndex)
						continue;
					if (_playerStateList[p]->GetX() == x && _playerStateList[p]->GetX() == y)
					{
						cellValue = 1;
						break;
					};
				};
			};
			res[x][y] = cellValue;
		};
	return res;
}

EMovementDirection GetMovementDirection(int dx, int dy) {
	EMovementDirection direction;
	if (dx == 0 && dy == 0) {
		direction = EMovementDirection::NONE;
	}
	else if (dx == -1 && dy == 0) {
		direction = EMovementDirection::UP;
	}
	else if (dx == -1 && dy == 1) {
		direction = EMovementDirection::UP_RIGHT;
	}
	else if (dx == 0 && dy == 1) {
		direction = EMovementDirection::RIGHT;
	}
	else if (dx == 1 && dy == 1) {
		direction = EMovementDirection::DOWN_RIGHT;
	}
	else if (dx == 1 && dy == 0) {
		direction = EMovementDirection::DOWN;
	}
	else if (dx == 1 && dy == -1) {
		direction = EMovementDirection::DOWN_LEFT;
	}
	else if (dx == 0 && dy == -1) {
		direction = EMovementDirection::LEFT;
	}
	else if (dx == -1 && dy == -1) {
		direction = EMovementDirection::UP_LEFT;
	}
	return direction;
}

IPlayerState* GetPlayerState(int x, int y, int xVelocity, int yVelocity) {
	return new PlayerState(x, y, xVelocity, yVelocity);
}

IMap* GetDefaultMap() {
	return new Map();
}

IMap* GetMap(const std::vector< std::vector < int > > &inputCells,
	const std::pair< int, int > &_leftFinishPoint,
	const std::pair< int, int > &_rightFinishPoint)
{
	return new Map(inputCells, _leftFinishPoint, _rightFinishPoint);
}

int DynamicProgrammingStrategyFunc(const Map &map, const PlayerState &currentPlayer) {
	static CDynamicProgrammingStrategy strategy(map, currentPlayer);
	auto step = strategy.GetNextPosition();
	return (int)GetMovementDirection(currentPlayer.GetX() - step.first, currentPlayer.GetY() - step.second);
}

int AStarStrategyFunc(const Map &map, const PlayerState &currentPlayer) {
	fillAStarMap(map);
	AStarStrategyOnYAGSBPL aStarStrategyOnYAGSBPL;
	SNode start(currentPlayer.GetX(), currentPlayer.GetY(), currentPlayer.GetXVelocity(), currentPlayer.GetYVelocity());
	SNode finish(1,1,1,1); // нужно задать финишную линюю
	SNode step = aStarStrategyOnYAGSBPL.searchPath(start, finish);
	return (int)GetMovementDirection(currentPlayer.GetX() - step.position.first, currentPlayer.GetY() - step.position.second);
}

int StrategyFunc(const IMap &_map, const std::vector< std::shared_ptr<IPlayerState> > &_playerStates, int curPlayerPosition){
	Map map = /*PutPlayersOnMap(*/*(dynamic_cast<const Map*>(&_map))/*, _playerStates, curPlayerPosition)*/;
	const PlayerState currentPlayer = *(std::dynamic_pointer_cast<PlayerState>(_playerStates[curPlayerPosition]));

	/*srand(time(0));
	if (rand() % 2)
		return AStarStrategyFunc(map, currentPlayer);
	else*/
		return DynamicProgrammingStrategyFunc(map, currentPlayer);
};
