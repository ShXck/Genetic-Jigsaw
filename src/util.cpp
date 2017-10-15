
#include "util.h"
#include <algorithm>

namespace util {

	int random_int( int min, int max ) {
		std::random_device rd;
		std::mt19937 gen( rd() );
		std::uniform_int_distribution<> dist( min, max );
		return dist( gen );
	}

	float random_float( int min, int max ) {
	    std::random_device e;
	    std::mt19937 gen( e() );
	    std::uniform_real_distribution<> dis( min, max );
	    return dis(e);
	}

	bool contains_int( std::vector<int> v, int a ) {
		if( std::find( v.begin(), v.end(), a ) != v.end() ) {
			return true;
		}
		return false;
	}

} /* namespace util */
