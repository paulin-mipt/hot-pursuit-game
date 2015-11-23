//
//  CAStarStrategyOnYAGSBPL.hpp
//  AI-ABBYY
//
//  Created by Alexander Danilyak on 11/10/15.
//  Copyright © 2015 Alexander Danilyak. All rights reserved.
//

#ifndef CAStarStrategyOnYAGSBPL_hpp
#define CAStarStrategyOnYAGSBPL_hpp

#include <iostream>
#include <memory>
#include "SNode.hpp"
#include "CMap.hpp"
#include <functional>

class AStarStrategyOnYAGSBPL {
public:
	SNode searchPath(SNode &start, SNode &finish);
};

void fillAStarMap(const Map &map);

#endif /* CAStarStrategyOnYAGSBPL_hpp */
