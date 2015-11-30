﻿#pragma once

#include <set>
#include <vector>
#include <thread>
#include <Windows.h>

#include "UI/MapSettingsWindow.h"
#include "UI/GameResultWindow.h"

namespace Core {
	struct CCoordinates;
	class CPlayer;
	class CMap;
}

namespace UI {
	class CMainMenuWindow;
}

class CUIManager {
public:
	CUIManager( UI::CMainMenuWindow* mainMenuWindow, HINSTANCE hInst );

	int GetDirection( const std::vector<Core::CCoordinates>& possibleMoves, Core::CCoordinates inertia, Core::CCoordinates position ) const;
	void InitMap( const Core::CMap& map, const std::vector<Core::CPlayer>& players, const Core::CLine& start, const Core::CLine& finish ) const;
	void Move( const std::vector<Core::CPlayer>& movedPlayers ) const;
	void ShowCollisions( const std::set<Core::CPlayer>& collidedPlayers ) const;
	void ShowCrashes( const std::set<Core::CPlayer>& crashedPlayers ) const;
	void ShowGameResult( const Core::CPlayer* winner ) const;
	void SwitchToMainMenu() const;
	void SwitchToSettings() const;
	void SwitchToGame() const;
	void SwitchToResults() const;
	std::thread* GetUIThread();
	void FinishGame() const;
	void FinishUIThread() const;
	void MarkPossibleMoves(const std::vector<Core::CCoordinates>& possibleMoves) const;
	void UnMarkPossibleMoves(const std::vector<Core::CCoordinates>& possibleMoves) const;

private:
	UI::CMainMenuWindow* mainMenuWindow;
	UI::CMapSettingsWindow mapSettingsWindow;
	UI::CGameResultWindow gameResultWindow;

	std::thread uiThread;
};