#include <string>

#include "resource.h"

#include "UIManager.h"
#include "GlobalDefinitions.h"
#include "Core/Reader.h"
#include "Core/Game.h"
#include "UI/MapSettingsWindow.h"
#include "UI/Drawing.h"

const wchar_t* const UI::CMapSettingsWindow::className = L"CMapSettingsWindow";

bool UI::CMapSettingsWindow::RegisterClass( HINSTANCE hInst )
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
	tag.hIcon = reinterpret_cast< HICON > (::LoadImage( hInst, MAKEINTRESOURCE( IDI_MAIN_ICON ), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR ));
	tag.hIconSm = reinterpret_cast< HICON > (::LoadImage( hInst, MAKEINTRESOURCE( IDI_MAIN_ICON ), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR ));

	return !RegisterClassEx( &tag );
}

UI::CMapSettingsWindow::CMapSettingsWindow( CUIManager* _manager ) :
	handle( nullptr ),
	startGameButton( nullptr ),
	backToMenuButton( nullptr ),
	chooseMapButton( nullptr ),
	positionOwnerControls( std::vector<HWND>( 12, nullptr ) ),
	manager( _manager ),
	map( nullptr )
{
}

bool UI::CMapSettingsWindow::Create()
{
	handle = CreateWindow( className, L"Map settings - Rock'n'Roll race", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		200, 200, 400, 500, nullptr, nullptr, ::GetModuleHandle( nullptr ), this );

	chooseMapButton = CreateWindow( L"BUTTON", L"Choose map", WS_VISIBLE | WS_CHILD, 40, 50, 125, 20,
		handle, HMENU( BUTTON_CHOOSE_MAP ), HINSTANCE( GetWindowLong( handle, GWL_HINSTANCE ) ), this );
	for( int i = 0; i < positionOwnerControls.size(); ++i ) {
		positionOwnerControls[i] = CreateWindow( L"COMBOBOX", (std::wstring( L"Position " ) + std::to_wstring( i + 1 )).c_str(),
			CBS_DROPDOWNLIST | WS_VISIBLE | WS_CHILD | WS_VSCROLL, 40, 100 + 30 * i, 125, 80,
			handle, nullptr, HINSTANCE( GetWindowLong( handle, GWL_HINSTANCE ) ), this );
		::SendMessage( positionOwnerControls[i], CB_ADDSTRING, 0, LPARAM( L"None" ) );
		::SendMessage( positionOwnerControls[i], CB_ADDSTRING, 0, LPARAM( L"Player" ) );
		::SendMessage( positionOwnerControls[i], CB_ADDSTRING, 0, LPARAM( L"AI" ) );
		::SendMessage( positionOwnerControls[i], CB_SELECTSTRING, 0, LPARAM( L"None" ) );
	}
	startGameButton = CreateWindow( L"BUTTON", L"Start game", WS_VISIBLE | WS_CHILD, 225, 380, 150, 30,
		handle, HMENU( BUTTON_START_GAME ), HINSTANCE( GetWindowLong( handle, GWL_HINSTANCE ) ), this );
	backToMenuButton = CreateWindow( L"BUTTON", L"Back to main menu", WS_VISIBLE | WS_CHILD, 225, 430, 150, 30,
		handle, HMENU( BUTTON_BACK_TO_MENU ), HINSTANCE( GetWindowLong( handle, GWL_HINSTANCE ) ), this );
	CreateWindow( L"STATIC", L"After death", WS_CHILD | WS_VISIBLE | SS_CENTER,
		225, 300, 150, 20, handle, nullptr, HINSTANCE( GetWindowLong( handle, GWL_HINSTANCE ) ), this );
	mod = CreateWindow( L"COMBOBOX", L"Choose mod",
		CBS_DROPDOWNLIST | WS_VISIBLE | WS_CHILD | WS_VSCROLL | CBS_HASSTRINGS | WS_OVERLAPPED, 225, 330, 150, 80,
		handle, nullptr, HINSTANCE( GetWindowLong( handle, GWL_HINSTANCE ) ), this );
	::SendMessage( mod, CB_ADDSTRING, 0, LPARAM( L"Remove" ) );
	::SendMessage( mod, CB_ADDSTRING, 0, LPARAM( L"Start again" ) );
	::SendMessage( mod, CB_SELECTSTRING, 0, LPARAM( L"Remove" ) );
	return handle != nullptr;
}

void UI::CMapSettingsWindow::Destroy() const
{
	manager->FinishUIThread();
	glutDestroyWindow( UI::CDrawing::GetWindow() );
	manager->GetUIThread()->join();
	::PostQuitMessage( 0 );
}

void UI::CMapSettingsWindow::StartGame()
{
	int maxPlayerNumber = 0;
	try {
		if( map == nullptr ) {
			// no map
			::MessageBox( handle, L"No map chosen", L"You're doing it wrong", MB_ICONHAND );
		} else {
			maxPlayerNumber = map->GetStartPoints().size();
			std::vector<Core::CPlayer> playersInfo = GetPlayersInfo();
			bool startAgainIfDead = GetMod();
			if( playersInfo.empty() ) {
				// no players
				::MessageBox( handle, L"You need at least 1 player", L"You're doing it wrong", MB_ICONHAND );
			} else {
				// ok, we're ready to start
				Core::CGame game( *map, playersInfo, manager, startAgainIfDead );
				manager->SwitchToGame();
				game.Start();
			}
		}
	} catch( std::exception& e ) {
		if( std::string( "Can't open file" ) == e.what() ) {
			::MessageBox( handle, L"Map not found", L"You're doing it wrong", MB_ICONHAND );
		} else if( std::string( "Invalid number of players" ) == e.what() ) {
			std::wstring errorMessage = L"This map can hold only " + std::to_wstring( maxPlayerNumber ) + L" players";
			::MessageBox( handle, errorMessage.c_str(), L"You're doing it wrong", MB_ICONHAND );
		} else {
			::MessageBeep( SOUND_SYSTEM_BEEP );
			::PostQuitMessage( 1 );
		}
	}
}

void UI::CMapSettingsWindow::ChooseMap()
{
	try {
		Core::CReader reader;

		wchar_t currPath[_MAX_PATH] = L"";
		::GetCurrentDirectory( _MAX_PATH, currPath );

		wchar_t szFilePathName[_MAX_PATH] = L"";
		OPENFILENAME ofn = { 0 };
		ofn.lStructSize = sizeof( OPENFILENAME );
		ofn.hwndOwner = handle;
		ofn.lpstrFilter = L"Race map files (*.rcmap)\0*.rcmap\0All files (*.*)\0*.*\0";
		ofn.lpstrFile = szFilePathName;
		ofn.lpstrDefExt = L"rcmap";
		ofn.nMaxFile = _MAX_PATH;
		ofn.lpstrTitle = L"Choose map";
		ofn.Flags = OFN_READONLY;

		::GetOpenFileName( &ofn );
		::SetCurrentDirectory( currPath );

		map = std::make_shared<Core::CMap>( reader.ReadMap( ofn.lpstrFile ) );

	} catch( std::exception& e ) {
		if( std::string( "Can't open file" ) == e.what() ) {
			::MessageBox( handle, L"Map not found", L"You're doing it wrong", MB_ICONHAND );
		} else {
			::MessageBeep( SOUND_SYSTEM_BEEP );
			::PostQuitMessage( 1 );
		}
	}
}

void UI::CMapSettingsWindow::BackToMenu() const
{
	manager->SwitchToMainMenu();
}

//std::string UI::CMapSettingsWindow::GetMapName() const
//{
//	const size_t MAX_LENGTH = 1024;
//	std::shared_ptr<wchar_t> editText = std::shared_ptr<wchar_t>( new wchar_t[MAX_LENGTH] );
//	::GetWindowText( mapNameControl, editText.get(), MAX_LENGTH );
//	std::string result;
//	for( auto c : std::wstring( editText.get() ) ) {
//		result.push_back( c );
//	}
//	return result;
//}

std::vector<Core::CPlayer> UI::CMapSettingsWindow::GetPlayersInfo()
{
	const std::vector<Core::CCoordinates> playerStartCoordinates = map->GetStartPoints();
	const int maxPlayerNumber = playerStartCoordinates.size();

	int playerNumber = 0;
	std::vector<Core::CPlayer> result;
	const size_t MAX_LENGTH = 1024;
	std::shared_ptr<wchar_t> text = std::shared_ptr<wchar_t>( new wchar_t[MAX_LENGTH] );
	for( int i = 0; i < positionOwnerControls.size() && playerNumber <= maxPlayerNumber; ++i ) {
		::GetWindowText( positionOwnerControls[i], text.get(), MAX_LENGTH );
		std::wstring textString( text.get() );
		if( textString == L"Player" ) {
			if( playerNumber >= maxPlayerNumber ) {
				throw(std::runtime_error( "Invalid number of players" ));
			}
			result.push_back( Core::CPlayer( playerStartCoordinates[playerNumber], playerNumber, USER ) );
			playerNumber++;
		} else if( textString == L"AI" ) {
			if( playerNumber >= maxPlayerNumber ) {
				throw(std::runtime_error( "Invalid number of players" ));
			}
			result.push_back( Core::CPlayer( playerStartCoordinates[playerNumber], playerNumber, AI ) );
			playerNumber++;
		}
	}
	return result;
}

bool UI::CMapSettingsWindow::GetMod()
{
	const size_t MAX_LENGTH = 1024;
	LPWSTR text = new wchar_t[MAX_LENGTH];
	::GetWindowText( mod, text, MAX_LENGTH );
	std::wstring textString( text );
	if( textString == L"Start again" ) {
		return true;
	} else if( textString == L"Remove" ) {
		return false;
	}

}

void UI::CMapSettingsWindow::MakeVisible() const
{
	::ShowWindow( handle, SW_SHOW );
}

void UI::CMapSettingsWindow::MakeInvisible() const
{
	::ShowWindow( handle, SW_HIDE );
}

LRESULT UI::CMapSettingsWindow::windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam )
{
	CMapSettingsWindow* wnd;
	if( message == WM_NCCREATE ) {
		wnd = static_cast< CMapSettingsWindow* >(LPCREATESTRUCT( lParam )->lpCreateParams);
		::SetWindowLong( handle, GWL_USERDATA, LONG( LPCREATESTRUCT( lParam )->lpCreateParams ) );
		wnd->handle = handle;
	}
	wnd = reinterpret_cast< CMapSettingsWindow* >(::GetWindowLong( handle, GWL_USERDATA ));

	switch( message ) {
		case WM_DESTROY:
			wnd->Destroy();
			return 0;

		case WM_COMMAND:
			if( wParam == wnd->BUTTON_START_GAME ) {
				wnd->StartGame();
			} else if( wParam == wnd->BUTTON_CHOOSE_MAP ) {
				wnd->ChooseMap();
			} else if( wParam == wnd->BUTTON_BACK_TO_MENU ) {
				wnd->BackToMenu();
			}
			return 0;
	}

	return ::DefWindowProc( handle, message, wParam, lParam );
}