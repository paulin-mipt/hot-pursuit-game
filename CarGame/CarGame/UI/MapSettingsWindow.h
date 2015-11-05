#pragma once

#include <Windows.h>

namespace UI {
	class CMapSettingsWindow {
	public:
		static bool RegisterClass( HINSTANCE hInst );

		CMapSettingsWindow();

		bool Create();
		void Destroy();

		void Show( int cmdShow );
		void StartGame();

	private:
		HWND handle;

		static const wchar_t* const className;

		static LRESULT __stdcall windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam );
	};
}