#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <math.h>
#include <fstream>
#include "IPlayerState.h"
#include "IMap.h"
#include <windows.h>

typedef int(__cdecl *STRATEGY_PROC)(const IMap &_map, const std::vector<std::shared_ptr<IPlayerState>> &_playerStates, int curPlayerPosition);
typedef IPlayerState*(__cdecl *PLAYER_STATE_FACTORY_PROC)(int x, int y, int xVelocity, int yVelocity);
typedef IMap*(__cdecl *MAP_FACTORY_PROC)(const std::vector< std::vector < int > > &inputCells,
	const std::pair< int, int > &_leftFinishPoint,
	const std::pair< int, int > &_rightFinishPoint);

class AITest
{
	HINSTANCE hinstLib;
	STRATEGY_PROC StrategyFunc;
	PLAYER_STATE_FACTORY_PROC GetPlayerState;
	MAP_FACTORY_PROC GetMap;
	std::vector<std::vector<int> > map;
	std::vector<std::pair<int, int> > positions;
	std::vector<std::pair<int, int> > velocity;
	std::vector<std::pair<int, int> > finish;
	std::pair<int, int> finishBegin;
	std::pair<int, int> finishEnd;
	
	void calcFinish();

	bool isFinish(int i, int j);
	int isGamer(int i, int j);
	void draw();

	void ProcessState(int k, int dx, int dy);

	void getStep();

	void readMap(std::string mapFile);
	
	void doAI(int k);

public:
	AITest();
	/*
	file:
	playersCount player1Positions.x player1Positions.y player2Positions.x player2Positions.y
	n m
	map - n rows  m cols
	FinishBegin.x FinishBegin.y FinishEnd.x FinishEnd.y
	*/
	void doTest(std::string mapFile = "map.txt");
};
