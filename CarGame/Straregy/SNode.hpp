//
//  SNode.hpp
//  AI-ABBYY
//
//  Created by Alexander Danilyak on 11/10/15.
//  Copyright © 2015 Alexander Danilyak. All rights reserved.
//

#ifndef SNode_h
#define SNode_h

enum class EMovementDirection : int {
	NONE = 0,
	UP = 1,
	UP_RIGHT = 2,
	RIGHT = 3,
	DOWN_RIGHT = 4,
	DOWN = 5,
	DOWN_LEFT = 6,
	LEFT = 7,
	UP_LEFT = 8,
	START_POSITION = 9,
	FINISH_POSITION = 10
};

static void printMovementDiection(EMovementDirection direction) {
	if (direction == EMovementDirection::NONE) {
		std::cout << "[0] STAY" << std::endl;
	}
	else if (direction == EMovementDirection::UP) {
		std::cout << "[1] GO UP" << std::endl;
	}
	else if (direction == EMovementDirection::UP_RIGHT) {
		std::cout << "[2] GO UP AND RIGHT" << std::endl;
	}
	else if (direction == EMovementDirection::RIGHT) {
		std::cout << "[3] GO RIGHT" << std::endl;
	}
	else if (direction == EMovementDirection::DOWN_RIGHT) {
		std::cout << "[4] GO DOWN AND RIGHT" << std::endl;
	}
	else if (direction == EMovementDirection::DOWN) {
		std::cout << "[5] GO DOWN" << std::endl;
	}
	else if (direction == EMovementDirection::DOWN_LEFT) {
		std::cout << "[6] GO DOWN AND LEFT" << std::endl;
	}
	else if (direction == EMovementDirection::LEFT) {
		std::cout << "[7] GO LEFT" << std::endl;
	}
	else if (direction == EMovementDirection::UP_LEFT) {
		std::cout << "[8] GO UP AND LEFT" << std::endl;
	}
	else if (direction == EMovementDirection::START_POSITION) {
		std::cout << "[9] IT'S START!" << std::endl;
	}
	else if (direction == EMovementDirection::FINISH_POSITION) {
		std::cout << "[10] IT'S FINISH!" << std::endl;
	}
}

struct SNode {
	std::pair< int, int > position;
	std::pair< int, int > velocityVector;

	SNode() {
		position = std::make_pair(0, 0);
		velocityVector = std::make_pair(0, 0);
		direction = EMovementDirection::START_POSITION;
	}

	SNode(int x, int y, int velocityX, int velocityY) :
		position(std::make_pair(x, y)),
		velocityVector(std::make_pair(velocityX, velocityY)) {
		direction = EMovementDirection::START_POSITION;
	}

	bool operator== (const SNode& node) {
		return (this->position.first == node.position.first && this->position.second == node.position.second);
	}

	EMovementDirection direction;

	void setDirection(int x, int y) {
		if (x == 0 && y == 0) {
			direction = EMovementDirection::NONE;
		}
		else if (x == -1 && y == 0) {
			direction = EMovementDirection::UP;
		}
		else if (x == -1 && y == 1) {
			direction = EMovementDirection::UP_RIGHT;
		}
		else if (x == 0 && y == 1) {
			direction = EMovementDirection::RIGHT;
		}
		else if (x == 1 && y == 1) {
			direction = EMovementDirection::DOWN_RIGHT;
		}
		else if (x == 1 && y == 0) {
			direction = EMovementDirection::DOWN;
		}
		else if (x == 1 && y == -1) {
			direction = EMovementDirection::DOWN_LEFT;
		}
		else if (x == 0 && y == -1) {
			direction = EMovementDirection::LEFT;
		}
		else if (x == -1 && y == -1) {
			direction = EMovementDirection::UP_LEFT;
		}
	}
};

#endif /* SNode_h */
