
#include "util.h"
#include <algorithm>

namespace util {

	int random_int( int min, int max ) {
		std::random_device rd;
		std::mt19937 gen( rd() );
		std::uniform_int_distribution<> dist( min, max );
		return dist( gen );
	}

	bool contains_int( std::vector<int> v, int a ) {
		if( std::find( v.begin(), v.end(), a ) != v.end() ) {
			return true;
		}
		return false;
	}

} /* namespace util */
