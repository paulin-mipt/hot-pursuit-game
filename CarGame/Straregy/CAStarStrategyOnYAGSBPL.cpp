//
//  CAStarStrategyOnYAGSBPL.cpp
//  AI-ABBYY
//
//  Created by Alexander Danilyak on 11/10/15.
//  Copyright © 2015 Alexander Danilyak. All rights reserved.
//

#include <algorithm>
#include "CAStarStrategyOnYAGSBPL.hpp"
#include "yagsbpl_base.h"
#include "planners/A_star.h"

// ЭТА ШТУКА ДОЛЖНА ГДЕ-ТО ЗАПОЛНЯТЬСЯ!!!!
static std::shared_ptr<const Map > aStarStaticMap;

void fillAStarMap(const Map &map) {
	const std::shared_ptr<const Map > aStarStaticMap = std::shared_ptr<const Map >(&map);
}

int getHashBin(SNode& node) {
	int nodeSum = node.position.first;
	return nodeSum % std::max(aStarStaticMap->sizeOnXaxis(), aStarStaticMap->sizeOnYaxis());
}

bool isAccessible(SNode& node) {
	bool mapClassSol = aStarStaticMap->canPlayerStayOnCell(node.position.first, node.position.second);
	/*bool hardCodeSol;
	int i = node.position.first;
	int j = node.position.second;
	if (i >= 10 && j >= 10 && i < 20 && j < 20) {
	hardCodeSol = false;
	} else if (i == 15 && j < 20) {
	hardCodeSol = false;
	} else {
	hardCodeSol = true;
	}
	if (mapClassSol != hardCodeSol) {
	std::cout << "FUCKING FUCK " << i << " " << j << std::endl;
	}
	*/
	return mapClassSol;
}

void getSuccessors(SNode& node, std::vector<SNode>* s, std::vector<double>* c) {
	SNode reachableNode;
	for (int deltaX = -1; deltaX <= 1; ++deltaX) {
		for (int deltaY = -1; deltaY <= 1; ++deltaY) {
			if (deltaX == 0 && deltaY == 0 && node.velocityVector.first == 0 && node.velocityVector.second == 0) {
				continue;
			}

			reachableNode.position = std::make_pair(node.position.first + node.velocityVector.first + deltaX,
				node.position.second + node.velocityVector.second + deltaY);

			reachableNode.velocityVector = std::make_pair(node.velocityVector.first + deltaX,
				node.velocityVector.second + deltaY);

			reachableNode.setDirection(deltaX, deltaY);

			if (reachableNode.position.first > 0 &&
				reachableNode.position.second > 0 &&
				reachableNode.position.first < aStarStaticMap->sizeOnXaxis() &&
				reachableNode.position.second < aStarStaticMap->sizeOnYaxis() /*&&
																			  aStarStaticMap->canPlayerMoveFromThisPositionWithSuchVector(node.position.first,
																			  node.position.second,
																			  reachableNode.velocityVector.first,
																			  reachableNode.velocityVector.second)*/)
			{
				//std::cout << "ReachableNode: " << reachableNode.position.first << " " << reachableNode.position.second << std::endl;
				s->push_back(reachableNode);
				c->push_back(1);
			}
		}
	}
}

double getHeuristics(SNode& node1, SNode& node2) {
	return std::max(abs(node1.position.first - node2.position.first), abs(node1.position.second - node2.position.second));
}

SNode AStarStrategyOnYAGSBPL::searchPath(SNode& start, SNode& finish) {
	GenericSearchGraphDescriptor<SNode, double> graph;

	graph.getHashBin_fp = &getHashBin;
	//graph.getHeuristics_fp = &getHeuristics;
	graph.getSuccessors_fp = &getSuccessors;
	graph.isAccessible_fp = &isAccessible;

	graph.hashTableSize = (int)std::max(aStarStaticMap->sizeOnXaxis(), aStarStaticMap->sizeOnYaxis()) + 1;

	graph.SeedNode = start;
	graph.TargetNode = finish;

	A_star_planner<SNode, double> planner;
	planner.init(graph);
	planner.plan();

	std::vector< std::vector< SNode > > paths = planner.getPlannedPaths();
	/*
	printf("Number of paths: %lu\nPath coordinates: \n[ ", paths.size());
	if (paths.size() > 0) {
	for (int a=0; a<paths[0].size(); a++) {
	printf("[%d, %d]{%d}; ", paths[0][a].position.first+1, paths[0][a].position.second+1, paths[0][a].direction);
	}
	printf(" ]\n\n");
	}
	*/
	if (paths.size() > 0) {
		int pathSize = (int)paths[0].size();
		return paths[0][pathSize - 2];
	}
	else {
		std::cout << "!!!NO PATH FOUND!!!" << std::endl;
		return SNode(-1, -1, 0, 0);
	}
}
