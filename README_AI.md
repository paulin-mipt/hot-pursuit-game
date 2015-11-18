В данном репозитории находится динамическая библиотека AI для игры "Гонки".

С командой движка был обговорен API библиотеки. В движок экспортируются классы, описываемые интерфейсами:
>> IMap

>> IPlayerState

Factory-функции для них:
>> GetPlayerState(int x, int y, int xVelocity, int yVelocity)

Дефолтная карта:
>> GetMap()

Карта, заполняемая данными из inputCells, 
с финишной линией, задаваемой двумя точками _leftFinishPoint, _rightFinishPoint:
>> GetMap(const std::vector< std::vector < int > > &inputCells,
>> 	const std::pair< int, int > &_leftFinishPoint,
>> 	const std::pair< int, int > &_rightFinishPoint)

Функция стратегии:
>> int StrategyFunc(const IMap &_map, const std::vector<std::shared_ptr<IPlayerState>> &_playerStates, int curPlayerPosition);

Здесь _playerStates - вектор указателей на PlayerState каждого из игроков, а curPlayerPosition - индекс игрока, совершающего ход.

StrategyFunc возвращает позицию (1-9) следующего хода для текущего игрока.

Требования, установленные командой движка можно посмотреть здесь: https://github.com/ngc696/PromProg_Race_CardRedactor/issues/1
