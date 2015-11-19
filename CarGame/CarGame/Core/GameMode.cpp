#include "Core/GameMode.h"

namespace Core {
	CGameMode::MovementMode CGameMode::movementMode = CONCURRENT;
	CGameMode::DeathPenalty CGameMode::deathPenalty = DESTROY;
	int CGameMode::lapCount = 1;
	CGameMode::ObjectRate CGameMode::objectRate = NO;

	void CGameMode::Init( MovementMode _movementMode, DeathPenalty _deathPenalty, int _lapCount, ObjectRate _objectRate )
	{
		movementMode = _movementMode;
		deathPenalty = _deathPenalty;
		lapCount = _lapCount;
		objectRate = _objectRate;
	}

	CGameMode::MovementMode CGameMode::GetMovementMode()
	{
		return movementMode;
	}

	CGameMode::DeathPenalty CGameMode::GetDeathPenalty()
	{
		return deathPenalty;
	}

	int CGameMode::GetLapCount()
	{
		return lapCount;
	}

	CGameMode::ObjectRate CGameMode::GetObjectRate()
	{
		return objectRate;
	}
}