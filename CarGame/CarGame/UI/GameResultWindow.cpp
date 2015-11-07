#include "UI/GameResultWindow.h"

bool UI::CGameResultWindow::RegisterClass( HINSTANCE hInst )
{
	return true;
}

UI::CGameResultWindow::CGameResultWindow() :
	handle( nullptr )
{}

bool UI::CGameResultWindow::Create()
{
	return true;
}

void UI::CGameResultWindow::MakeVisible() const
{
//	::ShowWindow( handle, SW_HIDE );
}

void UI::CGameResultWindow::MakeInvisible() const
{
//	::ShowWindow( handle, SW_SHOW );
}