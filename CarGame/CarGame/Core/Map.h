#pragma once

#include <vector>

namespace Core {
	typedef std::pair<size_t, size_t> CSize;
	typedef std::vector< std::vector<size_t> > CField;

	class CMap {
	public:
		CMap();

		CMap( const CField& newMap );

		~CMap();

		void print();
		void setPosition( int x, int y );
		void clearPosition( int x, int y );
		CSize getSize();
		bool isEmpty( int i, int j );

	private:
		CField map; // Карта (таблица), в которой 1 - препятствие (дороги нет). А 0 - дорога.
		CSize size;
	};
}