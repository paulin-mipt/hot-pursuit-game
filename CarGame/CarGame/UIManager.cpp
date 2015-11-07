#include <iostream>

#include "UIManager.h"
#include "Core/Player.h"
#include "Core/Map.h"
#include "UI/Drawing.h"
#include "UI/Map.h"
#include "UI/Car.h"
#include "UI/MainMenuWindow.h"

CUIManager::CUIManager( UI::CMainMenuWindow* _mainMenuWindow, HINSTANCE hInst ) :
	mainMenuWindow( _mainMenuWindow ),
	mapSettingsWindow( this ),
	uiThread( std::bind( UI::CDrawing::Init, 0, nullptr ) )
{
	UI::CMapSettingsWindow::RegisterClass( hInst );
	mapSettingsWindow.Create();
	
//	UI::CGameResultWindow::RegisterClass( hInst );
//	gameResultWindow.Create();
}

int CUIManager::GetDirection() const
{
	UI::CDrawing::DropKey();
	int key;
	while( (key = UI::CDrawing::GetKey()) == -1 ) {
		std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
	}
	return key;
}

void CUIManager::InitMap( const Core::CMap& map, const std::vector<Core::CPlayer>& players ) const
{
	Core::CField field = map.GetField();
	std::vector<std::vector<int>> newField;
	for( auto i = 0; i < field.size(); ++i ) {
		newField.push_back( std::vector<int>( 0 ) );
		for( auto j = 0; j < field[0].size(); ++j ) {
			newField[i].push_back( field[i][j] );
		}
	}

	std::vector<UI::CCar> cars;
	for( int i = 0; i < players.size(); ++i ) {
		auto playerCoordinates = players[i].GetPosition();
		cars.push_back( UI::CCar( UI::CCoordinates( playerCoordinates.x, playerCoordinates.y, PI / 2 ), UI::Color( i % 4 ) ) );
	}

	UI::CDrawing::InitGame( UI::CMap( newField ), cars );
	UI::CDrawing::Start();
}

void CUIManager::Move( const std::vector<Core::CPlayer>& movedPlayers ) const
{
	std::vector<int> numbers;
	std::vector<UI::CCoordinates> coordinates;
	for( auto player : movedPlayers ) {
		numbers.push_back( player.GetNumber() );
		coordinates.push_back( UI::CCoordinates( player.GetPosition().x, player.GetPosition().y ) );
	}
	UI::CDrawing::MoveCars( numbers, coordinates );
}

void CUIManager::ShowCollisions( const std::set<Core::CPlayer>& collidedPlayers ) const
{
	std::vector<int> numbers;
	std::vector<UI::CCoordinates> coordinates;
	for( auto player : collidedPlayers ) {
		numbers.push_back( player.GetNumber() );
		coordinates.push_back( UI::CCoordinates( player.GetInitialPosition().x, player.GetInitialPosition().y, PI / 2 ) );
	}
	UI::CDrawing::MoveCarsToStart( numbers, coordinates );
}

void CUIManager::ShowCrashes( const std::set<Core::CPlayer>& crashedPlayers ) const
{
	std::vector<int> numbers;
	for( auto player : crashedPlayers ) {
		numbers.push_back( player.GetNumber() );
	}
	UI::CDrawing::DeleteCars( numbers );
}

void CUIManager::ShowGameResult( const Core::CPlayer* winner ) const
{
//	if( winner == nullptr ) {
//		std::cout << "All players are dead." << std::endl;
//	} else {
//		std::cout << "Player number " << winner->GetNumber() + 1 << " is winner! Congratulations!!!" << std::endl;
//	}
//	std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
//	UI::CDrawing::Stop();
	SwitchToMainMenu();
}

void CUIManager::SwitchToMainMenu() const
{
	mainMenuWindow->MakeVisible();
	mapSettingsWindow.MakeInvisible();
//	gameResultWindow.MakeInvisible();
	UI::CDrawing::HideWindow();
}

void CUIManager::SwitchToSettings() const
{
	mainMenuWindow->MakeInvisible();
	mapSettingsWindow.MakeVisible();
//	gameResultWindow.MakeInvisible();
	UI::CDrawing::HideWindow();
}

void CUIManager::SwitchToGame() const
{
	mainMenuWindow->MakeInvisible();
	mapSettingsWindow.MakeInvisible();
//	gameResultWindow.MakeInvisible();
	UI::CDrawing::ShowWindow();
}

void CUIManager::SwitchToWinners() const
{
	mainMenuWindow->MakeInvisible();
	mapSettingsWindow.MakeInvisible();
//	gameResultWindow.MakeVisible();
//	UI::CDrawing::HideWindow();
}

std::thread* CUIManager::GetUIThread()
{
	return &uiThread;
}

void CUIManager::FinishGame() const
{
	UI::CDrawing::DropGame();
}

void CUIManager::FinishUIThread() const
{
	UI::CDrawing::Finish();
}

//std::vector<Core::CPlayer> CUIManager::GetPlayersInfo( const std::vector<Core::CCoordinates>& coordinates )
//{
//	int playerNumber = 0;
//	std::vector<UI::CMapSettingsWindow::CPositionInfo> positions = mapSettingsWindow.GetPositionsInfo();
//	std::vector<Core::CPlayer> result;
//	for( int i = 0; i < positions.size(); ++i ) {
//		if( positions[i].playerType == L"User" ) {
//			result.push_back( Core::CPlayer( coordinates[i], playerNumber++, USER ) );
//		} else if (positions[i].playerType == L"Computer") {
//			result.push_back( Core::CPlayer( coordinates[i], playerNumber++, AI ) );
//		}
//	}
//	return result;
//}

//std::string CUIManager::GetMapName()
//{
//	SwitchToSettings();
//	return "";
////	while ( mapSettingsWindow.GetState() == UI::CMapSettingsWindow::OPEN ) {
//////		std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );
////	}
////	if ( mapSettingsWindow.GetState() == UI::CMapSettingsWindow::OK ) {
////		return mapSettingsWindow.GetMapName();
////	}
////	if (mapSettingsWindow.GetState() == UI::CMapSettingsWindow::CANCEL ) {
////		return "";
////	}
////	throw std::runtime_error("Cannot get map name - settings window is closed");
//}