#pragma once

#include <Windows.h>

#include "resource.h"

namespace UI {
	class CGameResultWindow {
	public:
		static bool RegisterClass( HINSTANCE hInst );

		CGameResultWindow();

		bool Create();
//		void Destroy();
//
//		void Show( int cmdShow );
//		void StartGame();

		void MakeVisible() const;
		void MakeInvisible() const;

	private:
		HWND handle;

		static const wchar_t* const className;

//		static LRESULT __stdcall windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam );
	};
}