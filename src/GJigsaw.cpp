#include "GJigsaw.h"

G_Jigsaw::G_Jigsaw( ) : total_fitness( 0.0f ), current_generation( 0 ), final_solution( nullptr ) {
	srand( (int)time(NULL) );
	_population.resize( POPULATION_SIZE );
}

void G_Jigsaw::run() {

	start_population( );

	while( true ) {
		bool _found = false;

		while( !_found ) {
			for( int i = 0; i < POPULATION_SIZE; i++ ) {
				Individual curr = _population[i];
				curr._fitness = fitness_of( curr._solution );
				total_fitness += curr._fitness;
			}
			for( int i = 0; i < POPULATION_SIZE; i++ ) {
				Individual curr = _population[i];
				if( curr._fitness == 999.0f ) {
					std::cout << "SOLUTION FOUND!" << std::endl;
					final_solution = &curr;
					_found = true;
					break;
				}
			}

			evolve();

			if( current_generation > MAX_GENERATIONS ) {
				std::cout << "NO SOLUTION FOUND THIS RUN!" << std::endl;
				_found = true;
			}
		}
	}

}

void G_Jigsaw::evolve() {

	Population tmp_pop;
	tmp_pop.resize( POPULATION_SIZE );

	int pop_ctr = 0;

	while( pop_ctr < POPULATION_SIZE ) {
		Mat offspring1 = select_individual();
		Mat offspring2 = select_individual();

		crossover( offspring1, offspring2 );

		mutate( offspring1 );
		mutate( offspring2 );

		tmp_pop[pop_ctr++] = Individual( offspring1, 0.0f );
		tmp_pop[pop_ctr++] = Individual( offspring2, 0.0f );
	}

	for( int i = 0; i < POPULATION_SIZE; i++ ) {
		_population[i] = tmp_pop[i];
	}

	++current_generation;

}

void G_Jigsaw::start_population() {
	Mat r;
	for( int i = 0; i < POPULATION_SIZE; i++ ) {
		r = m_handler.join_parts();
		m_handler.create_img( "sol" +  std::to_string( i ) + ".jpg", r );
		_population.push_back( Individual( r, 0.0f ) );
	}
}

void G_Jigsaw::generate_population( int n_individuals ) {

}

int G_Jigsaw::fitness_of( Mat individual ) {
	return 0;
}

Mat G_Jigsaw::select_individual() {

}

void G_Jigsaw::crossover( Mat& img1, Mat& img2 ) {

}

void G_Jigsaw::mutate( Mat& individual ) {

}

void G_Jigsaw::restart() {
	_population.clear();
	total_fitness = 0.0f;
	current_generation = 0;
}

G_Jigsaw::~G_Jigsaw() { }

