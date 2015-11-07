#pragma once

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

	int GetDirection() const;
	void InitMap( const Core::CMap& map, const std::vector<Core::CPlayer>& players ) const;
	void Move( const std::vector<Core::CPlayer>& movedPlayers ) const;
	void ShowCollisions( const std::set<Core::CPlayer>& collidedPlayers ) const;
	void ShowCrashes( const std::set<Core::CPlayer>& crashedPlayers ) const;
	void ShowGameResult( const Core::CPlayer* winner ) const;
	void SwitchToMainMenu() const;
	void SwitchToSettings() const;
	void SwitchToGame() const;
	void SwitchToWinners() const;
	std::thread* GetUIThread();
	void FinishGame() const;
	void FinishUIThread() const;

private:
	UI::CMainMenuWindow* mainMenuWindow;
	UI::CMapSettingsWindow mapSettingsWindow;
	UI::CGameResultWindow gameResultWindow;

	std::thread uiThread;
};