﻿// Author: Evgeny Chernigovsky
// Description: 
#pragma once

#include "CStateArray.h"

// returns minimal x, that belongs to {x(x-1) / 2 > size}
int CStateArray::getMaxVelocityChange(int size) {
    return static_cast<int>(ceil((sqrt(8 * size + 1) + 1) / 2));
}

CStateArray::CStateArray(int xSize, int ySize, int value) {
    maxXVelocity = getMaxVelocityChange(xSize);
    maxYVelocity = getMaxVelocityChange(ySize);
    minXVelocity = -getMaxVelocityChange(xSize);
    minYVelocity = -getMaxVelocityChange(ySize);


    std::vector< std::pair<int, PlayerState> > yVelocityInitialize(
            maxYVelocity - minYVelocity + 1,
            std::make_pair(value, PlayerState(-1, -1, -1, -1))
    );
    std::vector< std::vector< std::pair<int, PlayerState> > > xVelocityInitialize(
            maxXVelocity - minXVelocity + 1,
            yVelocityInitialize
    );
    std::vector< std::vector< std::vector< std::pair<int, PlayerState> > > > yAxisInitialize(
            ySize,
            xVelocityInitialize
    );
    stateArray.assign(xSize, yAxisInitialize);
}

int CStateArray::GetStepCount(const PlayerState &state) const {
    return stateArray[state.GetX()][state.GetY()][state.GetXVelocity() - minXVelocity]
            [state.GetYVelocity() - minYVelocity].first;
}

void CStateArray::SetStepCount(const PlayerState &state, int value) {
    stateArray[state.GetX()][state.GetY()][state.GetXVelocity() - minXVelocity]
            [state.GetYVelocity() - minYVelocity].first = value;
}

PlayerState CStateArray::GetPreviousState(const PlayerState &state) const {
    return stateArray[state.GetX()][state.GetY()][state.GetXVelocity() - minXVelocity]
            [state.GetYVelocity() - minYVelocity].second;
}

void CStateArray::SetPreviousState(const PlayerState &state, const PlayerState &previousState) {
    stateArray[state.GetX()][state.GetY()][state.GetXVelocity() - minXVelocity]
            [state.GetYVelocity() - minYVelocity].second = previousState;
}

int CStateArray::GetMinXVelocity() const {
	return minXVelocity;
}

int CStateArray::GetMaxXVelocity() const {
	return maxXVelocity;
}

int CStateArray::GetMinYVelocity() const {
	return minYVelocity;
}

int CStateArray::GetMaxYVelocity() const {
	return maxYVelocity;
}

/*int CStateArray::GetMinStepCount(PlayerState *optimalState) const {
    int minStepCount = -1;

    for (int xVelocity = minXVelocity; xVelocity < maxXVelocity; ++xVelocity) {
        for (int yVelocity = minYVelocity; yVelocity < maxYVelocity; ++yVelocity) {
            int currentStateStepCount =
                    stateArray[x][y][xVelocity - minYVelocity][yVelocity - minYVelocity].first;
            if (currentStateStepCount != -1 &&
                    (minStepCount == -1 || minStepCount > currentStateStepCount)) {
                minStepCount = currentStateStepCount;
                optimalState->SetXVelocity(xVelocity);
                optimalState->SetYVelocity(yVelocity);
            }
        }
    }

    return minStepCount;
}
*/