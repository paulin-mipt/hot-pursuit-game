#pragma once

#include <Windows.h>

namespace Core {
	class CMap;

	class CReader {
	public:
		CMap ReadMap( LPWSTR path );
	};
}