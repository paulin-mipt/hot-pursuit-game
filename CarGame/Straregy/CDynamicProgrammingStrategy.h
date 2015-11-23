// Author: Evgeny Chernigovsky
// Description: Dynamic programming O(n^3) solution, where n is a linear size of map.
#pragma once

#ifndef AI_ABBYY_CDYNAMICPROGRAMMINGSTRATEGY_H
#define AI_ABBYY_CDYNAMICPROGRAMMINGSTRATEGY_H


#include "CPlayerState.hpp"
#include "CMap.hpp"
#include "CStateArray.h"
#include "CStrategy.h"
#include <vector>
#include <queue>
#include <stack>

class CDynamicProgrammingStrategy : CStrategy {
private:
    Map map;
    PlayerState initialState;

	int lastXDeviation;
	int lastYDeviation;

    const int UNREACHABLE = -1;

    // minimal path from initial state
    CStateArray minPath;

    std::queue<PlayerState> stateQueue;
    std::stack<PlayerState> optimalPath;

    void calculatePaths();
    int findMinStepCount(PlayerState *optimalFinish);
    void findOptimalPath();
	bool canIntersectFinishLine(PlayerState state, int &xDeviation_, int &yDeviation_) const;

public:
    CDynamicProgrammingStrategy(const Map &map, const PlayerState &initialState);

    std::pair<int, int> GetNextPosition();

    PlayerState GetNextState();
    bool HasNextState();

	int GetLastXDeviation() const;
	int GetLastYDeviation() const;
};

#endif //AI_ABBYY_CDYNAMICPROGRAMMINGSTRATEGY_H
