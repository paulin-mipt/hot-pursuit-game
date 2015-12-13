#pragma once

#include <Windows.h>

namespace UI {
	class CMapSettingsWindow;
	class CGameResultWindow;

	class CMainMenuWindow
	{
	public:
		static bool RegisterClass( HINSTANCE hInst );

		CMainMenuWindow( HINSTANCE hInst );

		bool Create();
		void Destroy();

		void Show( int cmdShow );
		void Play();
		void CallMapRedactor();

		void MakeVisible() const;
		void MakeInvisible() const;

	private:
		HWND handle;
		HWND newGameButton;
		HWND exitGameButton;
		HWND newMapButton;

		CUIManager manager;

		const int BUTTON_NEW_GAME = 1;
		const int BUTTON_EXIT = 2;
		const int BUTTON_MAP_REDACTOR = 3;
		const int OVERLAPPED_REDACTOR = 4;

		static const wchar_t* const className;

		static LRESULT __stdcall windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam );
	};
}