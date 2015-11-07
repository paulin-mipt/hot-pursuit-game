#include <string>
#include <iostream>
#include <thread>

#include "Core/Reader.h"
#include "Core/Game.h"
#include "GlobalDefinitions.h"
#include "UI/Drawing.h"
#include "UI/MainMenuWindow.h"
#include "UI/GameResultWindow.h"
#include "UI/MapSettingsWindow.h"

//int main( int argc, char* argv[] )
//{
//	using namespace Core;
//
//	CReader reader;
//	try {
//		CUIManager manager;
//		size_t mapNumber = manager.GetMapName();
//		CMap map = reader.ReadMap( RESOURCE_DIRECTORY + "Maps\\map" + std::to_string( mapNumber ) + ".txt" );
//		std::vector<CPlayer> playersInfo = manager.GetPlayersInfo( map.GetStartPoints() );
//		CGame game( map, playersInfo, manager );
//		std::thread t( std::bind( UI::CDrawing::Draw, argc, argv ) );
//		game.Start();
//
//		glutHideWindow();
//		std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );
//		glutShowWindow();
//		std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );
//		glutDestroyWindow( UI::CDrawing::GetWindow() );
//		t.join();
//	} catch( std::exception const &e ) {
//		std::cerr << e.what() << std::endl;
//	}
//
//	return 0;
//}

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