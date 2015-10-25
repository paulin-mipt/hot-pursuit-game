#include <vector>

#include "Graphics/Loader.h"
#include "Graphics/Map.h"

namespace Graphics {
	CLoader::CLoader( const std::string& map_file, const std::string& cars_file, CMap& map, std::vector<CCar>& cars )
	{
		color_dict["Red"] = Red;
		color_dict["Green"] = Green;
		color_dict["Blue"] = Blue;

		std::ifstream map_in( map_file );
		map = read_map( map_in );

		std::ifstream cars_in( cars_file );
		cars = read_cars( cars_in );
	}

	CMap CLoader::read_map( std::istream & input )
	{
		int n = 0,
			m = 0,
			cell = 0;
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

	std::vector<CCar> CLoader::read_cars( std::istream & input )
	{
		int n = 0,
			number_of_steps = 0;
		std::string color = "";
		input >> n;
		std::vector<CCar> cars;
		for( int i = 0; i < n; ++i ) {
			input >> color;
			input >> number_of_steps; // should it be the same for all cars?
			CCar car( color_dict[color] );
			for( int j = 0; j < number_of_steps; ++j ) {
				CCoordinates step;
				input >> step.x >> step.y;
				car.Push( step );
			}
			car.Calculate_angles();
			cars.push_back( car );
		}
		return cars;
	}
}