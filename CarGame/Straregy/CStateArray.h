// Author: Evgeny Chernigovsky
// Description: CPlayerState to int map
#pragma once

#ifndef AI_ABBYY_CSTATEARRAY_H
#define AI_ABBYY_CSTATEARRAY_H

#include <vector>
#include <cmath>
#include <utility>
#include "CPlayerState.hpp"


class CStateArray {
private:
    // Возможно стоит заменить на std::unordered_map< PlayerState, std::pair<int, PlayerState> >
    std::vector< std::vector< std::vector< std::vector < std::pair<int, PlayerState> > > > > stateArray;

    int minXVelocity;
    int minYVelocity;
    int maxXVelocity;
    int maxYVelocity;

    int getMaxVelocityChange(int size);

public:
    CStateArray(int xSize, int ySize, int xVelocity, int yVelocity, int value);

    int GetStepCount(const PlayerState &state) const;
    PlayerState GetPreviousState(const PlayerState &state) const;

    void SetStepCount(const PlayerState &state, int value);
    void SetPreviousState(const PlayerState &state, const PlayerState &previousState);

    int FindMinStepCountToPoint(int x, int y, PlayerState *optimalState) const;
};


#endif //AI_ABBYY_CSTATEARRAY_H
