#include "Graphics/Loader.h"
#include "GlobalDefinitions.h"

//void test( int argc, char* argv[] )
//{
//	int n = 50,
//		m = 50;
//	std::vector<Coordinates> car_data;
//	car_data.resize( n );
//	for( int i = 0; i < n; i++ ) {
//		car_data[i].x = i;
//		car_data[i].y = i;
//	}
//	Car mycar( car_data, 60, Red );
//	std::vector<Car> cars;
//
//	cars.push_back( mycar );
//
//	for( int i = 0; i < n / 2; i++ ) {
//		car_data[i].x = i * 2;
//		car_data[i].y = i * 2;
//	}
//	for( int i = n / 2; i < n; i++ ) {
//		car_data[i].x = 2 * (n - i);
//		car_data[i].y = 2 * (n - i);
//	}
//	Car mycar2( car_data, 60, Blue );
//	cars.push_back( mycar2 );
//
//	std::vector<std::vector<int>> data;
//	data.resize( n );
//	for( int i = 0; i < n; i++ ) {
//		data[i].resize( m );
//		for( int j = 0; j < m; j++ ) {
//			if( i == 0 || j == 0 || i == n - 1 || j == m - 1 ) {
//				data[i][j] = 1;
//			} else {
//				data[i][j] = 0;
//			}
//		}
//	}
//	Drawing drawing( data, cars );
//	drawing.draw( argc, argv );
//}

int main2( int argc, char * argv[] )
{
	//test( argc, argv );
	Graphics::CLoader loader( RESOURCE_DIRECTORY + "Maps\\map_file.txt", RESOURCE_DIRECTORY + "Maps\\cars_file.txt", argc, argv );
	return 0;
}