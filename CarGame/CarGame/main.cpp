#include "Core/Game.h"
#include "UI/MainMenuWindow.h"

int __stdcall wWinMain( HINSTANCE hInst, HINSTANCE /*hPrevInst*/, LPWSTR commandLine, int nCmdShow )
{
	UI::CMainMenuWindow mainWindow( hInst );
	UI::CMainMenuWindow::RegisterClass( hInst );
	mainWindow.Create();
	mainWindow.Show( nCmdShow );

	//Цикл обработки сообщений
	MSG msg;
	BOOL getMessageResult = 0;
	while( (getMessageResult = ::GetMessage( &msg, nullptr, 0, 0 )) != 0 ) {
		if( getMessageResult == -1 ) {
			return -1;
		}
		if( getMessageResult == WM_DESTROY ) {
			return 0;
		}
		::TranslateMessage( &msg );
		::DispatchMessage( &msg );
	}

	return static_cast<int>(msg.wParam);
}