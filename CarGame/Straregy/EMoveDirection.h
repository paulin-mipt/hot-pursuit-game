// Author: Evgeny Chernigovsky
// Description: 
#pragma once

#ifndef AI_ABBYY_EMOVEDIRECTION_H
#define AI_ABBYY_EMOVEDIRECTION_H

enum class EMovementDirection : int {
	UP = 1,
	UP_RIGHT = 2,
	RIGHT = 3,
	DOWN_RIGHT = 4,
	DOWN = 5,
	DOWN_LEFT = 6,
	LEFT = 7,
	UP_LEFT = 8,
	NOT_CHANGED = 9,
	NONE = 10
};

#endif //AI_ABBYY_EMOVEDIRECTION_H
