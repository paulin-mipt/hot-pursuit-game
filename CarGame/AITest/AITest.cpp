#include "AITest.h"

void AITest::calcFinish()
{
	finish.clear();
	std::pair<double, double> d(finishEnd.first - finishBegin.first, finishEnd.second - finishBegin.second);
	double l = sqrt(d.first*d.first + d.second*d.second);
	d.first /= l;
	d.second /= l;
	for (int i = 0; i < l; ++i)
		finish.push_back(std::pair<int, int>(finishBegin.first + d.first*i + 0.5, finishBegin.second + d.second*i + 0.5));
}

bool AITest::isFinish(int i, int j)
{
	for (int k = 0; k < finish.size(); ++k)
		if (finish[k].first == i && j == finish[k].second)
			return true;
	return false;
}

int AITest::isGamer(int i, int j)
{
	for (int k = 0; k < positions.size(); ++k)
		if (positions[k].first == i && j == positions[k].second)
			return k;
	return -1;
}

void AITest::draw() {
	system("CLS");
	for (int i = 0; i < map.size(); ++i)
	{
		for (int j = 0; j < map[i].size(); ++j)
		{
			int k = isGamer(i, j);
			if (k == -1)
			{
				if (isFinish(i, j))
					std::cout << '@';
				else
					std::cout << ((map[i][j] == 0) ? ' ' : '#');
			}
			else
				std::cout << k;
		}
		std::cout << '\n';
	}
}

void AITest::ProcessState(int k, int dx, int dy)
{
	velocity[k].first += dx;
	velocity[k].second += dy;
	positions[k].first += velocity[k].first;
	positions[k].second += velocity[k].second;
}

void AITest::getStep()
{
	int dx, dy;
	std::cout << "write dx:";
	std::cin >> dx;
	std::cout << "write dy:";
	std::cin >> dy;
	ProcessState(0, dx, dy);
}

void AITest::readMap(std::string mapFile)
{
	int n, m;
	std::ifstream f(mapFile);
	int gamsersCount;
	f >> gamsersCount;
	velocity.resize(gamsersCount, std::pair<int, int>(0, 0));
	positions.resize(gamsersCount);
	for (int i = 0; i < positions.size(); ++i)
		f >> positions[i].first >> positions[i].second;
	f >> n >> m;
	char c;
	map.resize(n, std::vector<int>(m));
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			f >> c;
			map[i][j] = (c == '1') ? 1 : 0;
		};
	};

	f >> finishBegin.first >> finishBegin.second >> finishEnd.first >> finishEnd.second;
	calcFinish();

};

void AITest::doAI(int k)
{
	std::shared_ptr<IMap> mapPtr(GetMap(map,finishBegin,finishEnd));

	// PlayerState currentState(0, 0, 0, 0);
	std::vector<std::shared_ptr<IPlayerState>> playerStates;
	for (int i = 0; i < positions.size(); ++i)
	{
		std::shared_ptr<IPlayerState> playerStatePtr(GetPlayerState(positions[i].first, positions[i].second, velocity[i].first, velocity[i].second));
		playerStates.push_back(playerStatePtr);
	}
	int direction = StrategyFunc(*mapPtr, playerStates, k);
	if (direction == 1) {
		ProcessState(k, 0, 1);
	}
	else if (direction == 2) {
		ProcessState(k, 1, 1);
	}
	else if (direction == 3) {

		ProcessState(k, 1,0);
	}
	else if (direction ==4) {
		ProcessState(k, 1, -1);
	}
	else if (direction == 5) {
		ProcessState(k, 0, -1);
	}
	else if (direction == 6) {
		ProcessState(k, -1, -1);
	}
	else if (direction == 7) {
		ProcessState(k, -1,0);
	}
	else if (direction == 8) {
		ProcessState(k, -1, 1);
	}
	else if (direction == 9) {
		ProcessState(k, 0, 0);
	}
	else
		ProcessState(k, 0, 0);
}

void AITest::doTest(std::string mapFile)
{
	readMap(mapFile);
	while (1)
	{
		draw();
		getStep();
		for (int i = 1; i < positions.size(); ++i)
		{
			doAI(i);
		};
	}
}

AITest::AITest()
{
	hinstLib = LoadLibrary(TEXT("StrategyDLL.dll"));
	StrategyFunc = (STRATEGY_PROC)GetProcAddress(hinstLib, "StrategyFunc");
	GetPlayerState = (PLAYER_STATE_FACTORY_PROC)GetProcAddress(hinstLib, "GetPlayerState");
	GetMap = (MAP_FACTORY_PROC)GetProcAddress(hinstLib, "GetMap");
}