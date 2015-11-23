// Author: Evgeny Chernigovsky
// Description:
#pragma once

#include <stdexcept>
#include "CDynamicProgrammingStrategy.h"

CDynamicProgrammingStrategy::CDynamicProgrammingStrategy(const Map &_map,
                                                         const PlayerState &_initialState)
    : map(_map)
    , initialState(_initialState)
    , minPath(
            _map.sizeOnXaxis(),
            _map.sizeOnYaxis(),
            UNREACHABLE
    )
{
    minPath.SetStepCount(initialState, 0);
    stateQueue.push(initialState);

    calculatePaths();
    findOptimalPath();
}

void CDynamicProgrammingStrategy::calculatePaths() {
    while (!stateQueue.empty()) {
        PlayerState currentState = stateQueue.front();

        for (int xDeviation = -1; xDeviation <= 1; ++xDeviation) {
            for (int yDeviation = -1; yDeviation <= 1; ++yDeviation) {
                PlayerState newState(
                        currentState.GetX() + currentState.GetXVelocity() + xDeviation,
                        currentState.GetY() + currentState.GetYVelocity() + yDeviation,
                        currentState.GetXVelocity() + xDeviation,
                        currentState.GetYVelocity() + yDeviation
                );

                if (newState.GetX() < 0 || newState.GetX() >= map.sizeOnXaxis()
                        || newState.GetY() < 0 || newState.GetY() >= map.sizeOnYaxis()
                        || !map.canPlayerStayOnCell(newState.GetX(), newState.GetY())
                        || map.hasBarrierOnPath(currentState.GetX(), currentState.GetY(),
                                newState.GetX(), newState.GetY())) {
                    continue;
                }

                if (minPath.GetStepCount(newState) == -1 ||
                        minPath.GetStepCount(newState) > minPath.GetStepCount(currentState) + 1) {
                    minPath.SetStepCount(newState, minPath.GetStepCount(currentState) + 1);
                    minPath.SetPreviousState(newState, currentState);
                    stateQueue.push(newState);
                }
            }
        }

        stateQueue.pop();
    }
}

bool CDynamicProgrammingStrategy::canIntersectFinishLine(PlayerState state, int &xDeviation_, int &yDeviation_) const {
	for (int xDeviation = -1; xDeviation <= 1; ++xDeviation) {
		for (int yDeviation = -1; yDeviation <= 1; ++yDeviation) {
			int newX = state.GetX() + state.GetXVelocity() + xDeviation;
			int newY = state.GetY() + state.GetYVelocity() + yDeviation;

			if (newX < 0 || newX >= map.sizeOnXaxis() ||
				newY < 0 || newY >= map.sizeOnYaxis()) {
				continue;
			}

			if (map.intersectFinishLine(state.GetX(), state.GetY(), newX, newY) &&
				!map.hasBarrierOnPath(state.GetX(), state.GetY(), newX, newY))
			{
				xDeviation_ = xDeviation;
				yDeviation_ = yDeviation;
				return true;
			}
		}
	}
	
	return false;
}

int CDynamicProgrammingStrategy::findMinStepCount(PlayerState* optimalFinish) {
    int minStepCount = -1;
	int xDeviation, yDeviation;

	for (int x = 0; x < map.sizeOnXaxis(); ++x) {
		for (int y = 0; y < map.sizeOnYaxis(); ++y) {
			for (int xVelocity = minPath.GetMinXVelocity(); xVelocity < minPath.GetMaxXVelocity(); ++xVelocity) {
				for (int yVelocity = minPath.GetMinYVelocity(); yVelocity < minPath.GetMaxYVelocity(); ++yVelocity) {
					// состояние из которого можно пересечь финишную линию за один ход
					PlayerState previousState(x, y, xVelocity, yVelocity);

					if (minPath.GetStepCount(previousState) == -1) {
						continue;
					}

					if (!canIntersectFinishLine(previousState, xDeviation, yDeviation)) {
						continue;
					}

					int currentStepCount = minPath.GetStepCount(previousState);

					if (currentStepCount != -1 && (minStepCount == -1 || currentStepCount < minStepCount)) {
						minStepCount = currentStepCount;
						*optimalFinish = previousState;
						lastXDeviation = xDeviation;
						lastYDeviation = yDeviation;
					}
				}
			}
		}
	}

	return minStepCount;
}

void CDynamicProgrammingStrategy::findOptimalPath() {
    PlayerState optimalFinish;
    int minStepCount = findMinStepCount(&optimalFinish);

    if (minStepCount == -1) {
        throw std::runtime_error("Can't find path to finish");
    }

    PlayerState currentState = optimalFinish;
    while (currentState != initialState) {
        optimalPath.push(currentState);
        currentState = minPath.GetPreviousState(currentState);
    }
}

std::pair<int, int> CDynamicProgrammingStrategy::GetNextPosition() {
    PlayerState nextState = optimalPath.top();
    optimalPath.pop();
    return std::make_pair(nextState.GetX(), nextState.GetY());
}

PlayerState CDynamicProgrammingStrategy::GetNextState() {
    PlayerState nextState = optimalPath.top();
    optimalPath.pop();
    return nextState;
}

bool CDynamicProgrammingStrategy::HasNextState() {
    return !optimalPath.empty();
}

int CDynamicProgrammingStrategy::GetLastXDeviation() const {
	return lastXDeviation;
}

int CDynamicProgrammingStrategy::GetLastYDeviation() const {
	return lastYDeviation;
}
