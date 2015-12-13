#pragma once

#include <Windows.h>
#include "Core/Player.h"
#include "Core/Map.h"

class CUIManager;

namespace UI {
	class CMapSettingsWindow {
	public:
		static bool RegisterClass( HINSTANCE hInst );

		CMapSettingsWindow( CUIManager* manager );

		bool Create();
		void Destroy() const;

		void StartGame();
		void ChooseMap();
		void BackToMenu() const;
		std::vector<Core::CPlayer> GetPlayersInfo();
		bool GetMod();

		void MakeVisible() const;
		void MakeInvisible() const;

	private:
		std::shared_ptr<Core::CMap> map;

		HWND handle;
		HWND startGameButton;
		HWND backToMenuButton;
		HWND chooseMapButton;
		HWND mod;

		std::vector<HWND> positionOwnerControls;

		CUIManager* manager;

		const int BUTTON_START_GAME = 1;
		const int BUTTON_BACK_TO_MENU = 2;
		const int BUTTON_CHOOSE_MAP = 3;

		static const wchar_t* const className;

		static LRESULT __stdcall windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam );
	};
}