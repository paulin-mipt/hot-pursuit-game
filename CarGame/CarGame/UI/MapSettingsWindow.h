#pragma once

#include <Windows.h>
#include <Core/Player.h>

class CUIManager;

namespace UI {
	class CMapSettingsWindow {
	public:
		static bool RegisterClass( HINSTANCE hInst );

		CMapSettingsWindow( CUIManager* manager );

		bool Create();
		void Destroy() const;

		void StartGame();
		void BackToMenu() const;
		std::string GetMapName() const;
		std::vector<Core::CPlayer> GetPlayersInfo( const std::vector<Core::CCoordinates>& coordinates );
		
		void MakeVisible() const;
		void MakeInvisible() const;

	private:
		HWND handle;
		HWND startGameButton;
		HWND backToMenuButton;
		HWND mapNameControl;
		std::vector<HWND> positionOwnerControls;

		CUIManager* manager;

		const int BUTTON_START_GAME = 1;
		const int BUTTON_BACK_TO_MENU = 2;

		static const wchar_t* const className;

		static LRESULT __stdcall windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam );
	};
}