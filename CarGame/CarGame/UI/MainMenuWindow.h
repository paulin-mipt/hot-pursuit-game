#pragma once

#include <Windows.h>

#include "MapSettingsWindow.h"

namespace UI {
	class CMainMenuWindow {
	public:
		static bool RegisterClass( HINSTANCE hInst );

		CMainMenuWindow();

		bool Create();
		void Destroy();

		void Show( int cmdShow );
		void Play();

	private:
		HWND handle;
		HWND newGameButton;
		HWND exitGameButton;

		CMapSettingsWindow mapSettingsWindow;

		static const wchar_t* const className;
		static const int MAIN_MENU_BUTTON_NEW_GAME;
		static const int MAIN_MENU_BUTTON_EXIT;

		static LRESULT __stdcall windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam );
	};
}