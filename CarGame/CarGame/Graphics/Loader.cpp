#include <vector>

#include "Graphics/Loader.h"
#include "Graphics/Map.h"

namespace Graphics {
	CLoader::CLoader( const std::string& map_file, const std::string& players_info_file, CMap& map, std::vector<std::shared_ptr<CCar>>& cars )
	{
		color_dict["Red"] = Red;
		color_dict["Green"] = Green;
		color_dict["Blue"] = Blue;

		std::ifstream map_in( map_file );
		map = read_map( map_in );

		std::ifstream cars_in( players_info_file );
		cars = read_cars( cars_in );
	}

	CMap CLoader::read_map( std::istream & input )
	{
		int n = 0;
		int m = 0;
		int cell = 0;
		input >> n >> m;

		std::vector<std::vector<int>> map_data;
		map_data.resize( n );
		for( int i = n - 1; i >= 0; i-- ) {
			map_data[i].resize( m );
			for( int j = 0; j < m; j++ ) {
				input >> cell;
				map_data[i][j] = cell;
			}
		}
		CMap map( map_data );
		return map;
	}

	std::vector<std::shared_ptr<CCar>> CLoader::read_cars( std::istream & input )
	{
		int n = 0;
		int number_of_steps = 0;
		std::string color = "";
		input >> n;
		std::vector<std::shared_ptr<CCar>> cars;
		for( int i = 0; i < n; ++i ) {
			input >> color;
			input >> number_of_steps; // should it be the same for all cars?
			std::shared_ptr<CCar> car(new CCar( color_dict[color] ));
			cars.push_back( car );
		}
		return cars;
	}
}