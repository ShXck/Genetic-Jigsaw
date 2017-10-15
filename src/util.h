
#include <random>
#include <stdlib.h>

namespace util {

	/**
	 * @param min el valor mínimo.
	 * @param max el valor máximo.
	 * @return un valor entre los límites dados.
	 */
	int random_int( int min, int max );

	/**
	 * Genera un decimal aleatorio.
	 * @param min límite inferior.
	 * @param max límite superior.
	 * @return un valor dentro de los límites.
	 */
	float random_float( int min, int max );

	/**
	 * Revisa si un vector contiene cierto número entero-
	 * @param v el vector de enteros.
	 * @param a el número que se quiere encontrar.
	 * @return si el vector contiene el número o no.
	 */
	bool contains_int( std::vector<int> v, int a );



} /* namespace util */

