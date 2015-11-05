#include "resource.h"

#include "UI/MapSettingsWindow.h"

const wchar_t* const UI::CMapSettingsWindow::className = L"CMainWindow";

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
	tag.hIcon = reinterpret_cast<HICON> (::LoadImage( hInst, MAKEINTRESOURCE( IDI_MAIN_ICON ), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR ));
	tag.hIconSm = reinterpret_cast<HICON> (::LoadImage( hInst, MAKEINTRESOURCE( IDI_MAIN_ICON ), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR ));

	return !RegisterClassEx( &tag );
}

UI::CMapSettingsWindow::CMapSettingsWindow() :
	handle( nullptr )
{}

bool UI::CMapSettingsWindow::Create()
{
	return true;
}

void UI::CMapSettingsWindow::Destroy()
{
	::PostQuitMessage( 0 );
}

void UI::CMapSettingsWindow::Show( int cmdShow )
{
	ShowWindow( handle, cmdShow );
}

void UI::CMapSettingsWindow::StartGame()
{
}

LRESULT UI::CMapSettingsWindow::windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam )
{
	CMapSettingsWindow* wnd = nullptr;
	if( message == WM_NCCREATE ) {
		wnd = static_cast<CMapSettingsWindow*>(LPCREATESTRUCT( lParam )->lpCreateParams);
		::SetWindowLong( handle, GWL_USERDATA, LONG( LPCREATESTRUCT( lParam )->lpCreateParams ) );
		wnd->handle = handle;
	}
	wnd = reinterpret_cast<CMapSettingsWindow*>(::GetWindowLong( handle, GWL_USERDATA ));

	switch( message ) {
		case WM_DESTROY:
			wnd->Destroy();
			return 0;

		case WM_COMMAND:
			return 0;
	}

	return ::DefWindowProc( handle, message, wParam, lParam );
}