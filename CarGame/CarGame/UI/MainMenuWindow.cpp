#include <string>
#include <thread>

#include "resource.h"

#include "UIManager.h"
#include "Core/Reader.h"
#include "Core/Game.h"
#include "UI/MainWindow.h"
#include "UI/Drawing.h"

const wchar_t* const UI::CMainMenuWindow::className = L"CMainWindow";
const int UI::CMainMenuWindow::MAIN_MENU_BUTTON_NEW_GAME = 1;
const int UI::CMainMenuWindow::MAIN_MENU_BUTTON_EXIT = 2;

bool UI::CMainMenuWindow::RegisterClass( HINSTANCE hInst )
{
	WNDCLASSEX tag;
	tag.cbSize = sizeof( WNDCLASSEX );
	tag.style = CS_HREDRAW | CS_VREDRAW;
	tag.lpfnWndProc = windowProc;
	tag.cbClsExtra = 0;
	tag.cbWndExtra = 0;
	tag.hCursor = LoadCursor( nullptr, IDC_ARROW );
	tag.hbrBackground = HBRUSH( GetStockObject( BLACK_BRUSH ) );
	tag.lpszMenuName = nullptr;
	tag.lpszClassName = className;
	tag.hInstance = ::GetModuleHandle( nullptr );
	tag.hIcon = reinterpret_cast<HICON> (::LoadImage( hInst, MAKEINTRESOURCE( IDI_MAIN_ICON ), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR ));
	tag.hIconSm = reinterpret_cast<HICON> (::LoadImage( hInst, MAKEINTRESOURCE( IDI_MAIN_ICON ), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR ));

	return !RegisterClassEx( &tag );
}

UI::CMainMenuWindow::CMainMenuWindow() :
	handle( nullptr ),
	newGameButton( nullptr ),
	exitGameButton( nullptr )
{}

bool UI::CMainMenuWindow::Create()
{
	std::wstring windowName( L"Main menu - Car Game 2015" );
	handle = CreateWindow( className, windowName.c_str(), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		100, 100, 300, 300, nullptr, nullptr, ::GetModuleHandle( nullptr ), this );

	newGameButton = CreateWindow( L"BUTTON", L"New game", WS_VISIBLE | WS_CHILD, 75, 100, 150, 30,
		handle, HMENU(MAIN_MENU_BUTTON_NEW_GAME), HINSTANCE( GetWindowLong( handle, GWL_HINSTANCE ) ), this );
	exitGameButton = CreateWindow( L"BUTTON", L"Exit game", WS_VISIBLE | WS_CHILD, 75, 150, 150, 30,
		handle, HMENU(MAIN_MENU_BUTTON_EXIT), HINSTANCE( GetWindowLong( handle, GWL_HINSTANCE ) ), this );

	return handle != nullptr;
}

void UI::CMainMenuWindow::Destroy()
{
	::PostQuitMessage( 0 );
}

void UI::CMainMenuWindow::Show( int cmdShow )
{
	ShowWindow( handle, cmdShow );
}

void UI::CMainMenuWindow::Play()
{
	Core::CReader reader;
	try {
		CUIManager manager;
		size_t mapNumber = manager.GetMapName();
		Core::CMap map = reader.ReadMap( RESOURCE_DIRECTORY + "Maps\\map" + std::to_string( mapNumber ) + ".txt" );
		std::vector<Core::CPlayer> playersInfo = manager.GetPlayersInfo( map.GetStartPoints() );
		Core::CGame game( map, playersInfo, manager );
		std::thread t( std::bind( UI::CDrawing::Draw, 0, nullptr ) );
		game.Start();

		glutDestroyWindow( UI::CDrawing::GetWindow() );
		t.join();
	} catch( std::exception& e ) {
//		std::cerr << e.what() << std::endl;
	}
}

LRESULT UI::CMainMenuWindow::windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam )
{
	CMainMenuWindow* wnd = nullptr;
	if( message == WM_NCCREATE ) {
		wnd = static_cast<CMainMenuWindow*>(LPCREATESTRUCT( lParam )->lpCreateParams);
		::SetWindowLong( handle, GWL_USERDATA, LONG( LPCREATESTRUCT( lParam )->lpCreateParams ) );
		wnd->handle = handle;
	}
	wnd = reinterpret_cast<CMainMenuWindow*>(::GetWindowLong( handle, GWL_USERDATA ));

	switch( message ) {
		case WM_DESTROY:
			wnd->Destroy();
			return 0;

		case WM_COMMAND:
			if( LOWORD( wParam ) == MAIN_MENU_BUTTON_NEW_GAME ) {

			}
			if( LOWORD( wParam ) == MAIN_MENU_BUTTON_EXIT ) {
				::SendMessage( wnd->handle, WM_DESTROY, wParam, lParam );
			}
			return 0;
	}

	return ::DefWindowProc( handle, message, wParam, lParam );
}