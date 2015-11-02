#include <string>
#include <iostream>
#include <thread>
#include <windows.h>
#include <memory>

#include "Core/Reader.h"
#include "Core/Game.h"
#include "GlobalDefinitions.h"
#include "UI/Drawing.h"
#include "IPlayerState.h"
#include "IMap.h"

typedef int(__cdecl *STRATEGY_PROC)(IMap &map, std::vector<IPlayerState> &playerStateList, int currentPlayer);
typedef IPlayerState*(__cdecl *PLAYER_STATE_FACTORY_PROC)(int x, int y, int xVelocity, int yVelocity);
typedef IMap*(__cdecl *MAP_FACTORY_PROC)();

void initializeAI( std::vector< std::vector< size_t > > map, int startX, int startY, int finishX, int finishY )
{
	HINSTANCE hinstLib = LoadLibrary(TEXT("StrategyDLL.dll"));
	STRATEGY_PROC StrategyFunc = (STRATEGY_PROC)GetProcAddress(hinstLib, "StrategyFunc");
	PLAYER_STATE_FACTORY_PROC GetPlayerState = (PLAYER_STATE_FACTORY_PROC)GetProcAddress(hinstLib, "GetPlayerState");
	MAP_FACTORY_PROC GetMap = (MAP_FACTORY_PROC)GetProcAddress(hinstLib, "GetMap");

	std::shared_ptr<IMap> mapPtr(GetMap());
	mapPtr->initializationMap( map );
	mapPtr->setFinishLine( startX, startY, finishX, finishY );
}

int main( int argc, char* argv[] )
{
	using namespace Core;

	CReader reader;
	try {
		CUIManager manager;
		size_t mapNumber = manager.GetMapNumber();
		CMap map = reader.ReadMap( RESOURCE_DIRECTORY + "Maps\\map" + std::to_string( mapNumber ) + ".txt" );
		std::vector<PlayersTypes> playersInfo = manager.GetPlayersInfo();
		CGame game( map, playersInfo, manager );
		std::thread t( std::bind( UI::CDrawing::Draw, argc, argv ) );
		game.Start();

		glutDestroyWindow( UI::CDrawing::GetWindow() );
		t.join();
	} catch( std::exception const &e ) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}