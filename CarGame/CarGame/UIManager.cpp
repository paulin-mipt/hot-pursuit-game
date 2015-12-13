﻿#include <iostream>

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
	gameResultWindow( this ),
	uiThread( std::bind( UI::CDrawing::Init, 0, nullptr ) )
{
	UI::CMapSettingsWindow::RegisterClass( hInst );
	mapSettingsWindow.Create();

	UI::CGameResultWindow::RegisterClass( hInst );
	gameResultWindow.Create();
}

int CUIManager::GetDirection( const std::vector<Core::CCoordinates>& possibleMoves, Core::CCoordinates inertia, Core::CCoordinates position ) const
{
	UI::CDrawing::DropKey();
	int key;

	UI::CDrawing::DropMouse();
	Core::CCoordinates mouse;
	while( ((key = UI::CDrawing::GetKey()) == -1 ) && ((mouse = UI::CDrawing::GetMouse(possibleMoves)) == Core::CCoordinates(-1, -1)) ) {
		std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );
	}
	if (key == -1) {
		Core::CCoordinates direction = mouse - inertia - position;
		key = 5 + direction.x + 3 * (-direction.y);
	}
	return key;
}

void CUIManager::InitMap( const Core::CMap& map, const std::vector<Core::CPlayer>& players, const Core::CLine& start, const Core::CLine& finish ) const
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

	UI::CDrawing::InitGame( UI::CMap( newField ), cars, start, finish );
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

void CUIManager::MarkPossibleMoves(const std::vector<Core::CCoordinates>& possibleMoves) const
{
	UI::CDrawing::MarkPossibleMoves(possibleMoves);
}

void CUIManager::UnMarkPossibleMoves(const std::vector<Core::CCoordinates>& possibleMoves) const
{
	UI::CDrawing::UnMarkPossibleMoves(possibleMoves);
}

void CUIManager::ShowExplosionAndStartAgain( const std::set<Core::CPlayer>& collidedPlayers, const std::set<Core::CPlayer>& crashedPlayers ) const
{
	std::vector<int> numbers;
	std::vector<UI::CCoordinates> coordinates;
	for( auto player : collidedPlayers ) {
		numbers.push_back( player.GetNumber() );
		coordinates.push_back( UI::CCoordinates( player.GetInitialPosition().x, player.GetInitialPosition().y, PI / 2 ) );
	}
	for( auto player : crashedPlayers ) {
		numbers.push_back( player.GetNumber() );
		coordinates.push_back( UI::CCoordinates( player.GetInitialPosition().x, player.GetInitialPosition().y, PI / 2 ) );
	}
	if( !numbers.empty() ) {
		UI::CDrawing::ExplodeCars( numbers );
		UI::CDrawing::MoveCarsToStart( numbers, coordinates );
	}
}

void CUIManager::ShowExplosionAndDie( const std::set<Core::CPlayer>& collidedPlayers, const std::set<Core::CPlayer>& crashedPlayers ) const
{
	std::vector<int> numbers;
	for( auto player : collidedPlayers ) {
		numbers.push_back( player.GetNumber() );
	}
	for( auto player : crashedPlayers ) {
		numbers.push_back( player.GetNumber() );
	}
	if( !numbers.empty() ) {
		UI::CDrawing::ExplodeCars( numbers );
		UI::CDrawing::DeleteCars( numbers );
	}
}

void CUIManager::ShowGameResult( const Core::CPlayer* winner ) const
{
	gameResultWindow.SetWinner( winner );
	std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
	UI::CDrawing::Stop();
	SwitchToResults();
}

void CUIManager::SwitchToMainMenu() const
{
	mainMenuWindow->MakeVisible();
	mapSettingsWindow.MakeInvisible();
	gameResultWindow.MakeInvisible();
	UI::CDrawing::HideWindow();
}

void CUIManager::SwitchToSettings() const
{
	mainMenuWindow->MakeInvisible();
	mapSettingsWindow.MakeVisible();
	gameResultWindow.MakeInvisible();
	UI::CDrawing::HideWindow();
}

void CUIManager::SwitchToGame() const
{
	mainMenuWindow->MakeInvisible();
	mapSettingsWindow.MakeInvisible();
	gameResultWindow.MakeInvisible();
	UI::CDrawing::ShowWindow();
}

void CUIManager::SwitchToResults() const
{
	mainMenuWindow->MakeInvisible();
	mapSettingsWindow.MakeInvisible();
	gameResultWindow.MakeVisible();
	UI::CDrawing::HideWindow();
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