#ifdef RACE_AI_EXPORTS
#define RACE_AI_API __declspec(dllexport) 
#else
#define RACE_AI_API __declspec(dllimport) 
#endif

#include "CDynamicProgrammingStrategy.h"
#include "IPlayerState.h"
#include "IMap.h"

extern "C" RACE_AI_API int StrategyFunc(const IMap &_map, const std::vector<std::shared_ptr<IPlayerState>> &_playerStates, int curPlayerPosition);

// Factories to export PlayerState and Map classes
extern "C" RACE_AI_API IPlayerState* GetPlayerState(int x, int y, int xVelocity, int yVelocity);

extern "C" RACE_AI_API IMap* GetDefaultMap();

extern "C" RACE_AI_API IMap* GetMap(const std::vector< std::vector < int > > &inputCells,
	const std::pair< int, int > &_leftFinishPoint,
	const std::pair< int, int > &_rightFinishPoint);
