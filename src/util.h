
#include <random>

namespace util {

	/**
	 * @param min el valor mínimo.
	 * @param max el valor máximo.
	 * @return un valor entre los límites dados.
	 */
	int random_int( int min, int max );

	bool contains_int( std::vector<int> v, int a );

} /* namespace util */

