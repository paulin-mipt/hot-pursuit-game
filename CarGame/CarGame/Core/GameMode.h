#pragma once

namespace Core {
	class CGameMode {
	public:
		enum MovementMode { CONCURRENT, SEQUENTIAL };
		enum DeathPenalty { DESTROY, TO_START, STOP };
		enum ObjectRate { NO, FEW, NORMAL, MANY };

		CGameMode() = delete;

		static void Init( MovementMode movementMode, DeathPenalty deathPenalty, int lapCount, ObjectRate objectRate );

		static MovementMode GetMovementMode();
		static DeathPenalty GetDeathPenalty();
		static int GetLapCount();
		static ObjectRate GetObjectRate();

	private:
		static MovementMode movementMode;
		static DeathPenalty deathPenalty;
		static int lapCount;
		static ObjectRate objectRate;
	};
}