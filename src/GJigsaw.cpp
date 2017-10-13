#include "GJigsaw.h"

G_Jigsaw::G_Jigsaw( ) : total_fitness( 0.0f ), current_generation( 0 ), final_solution( nullptr ) {
	srand( (int)time(NULL) );
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
		r = img_handler.join_parts();
		img_handler.create_img( "sol" +  std::to_string( i ) + ".jpg", r );
		_population.push_back( Individual( r, 0.0f ) );
	}
}

int G_Jigsaw::fitness_of( Mat individual ) {

	Coords& _coords = img_handler.coords();
	float _result = 0.0f;

	Mat& _base = img_handler.base();

	for( unsigned int i = 0; i < _coords.size(); i++ ) {
		auto c = _coords[i];
		Mat curr_roi = img_handler.crop( individual, c.first, c.second, img_handler.img_details().parts_width, img_handler.img_details().parts_height, "tmp" );
		Mat base_roi = img_handler.crop( _base , c.first, c.second, img_handler.img_details().parts_width, img_handler.img_details().parts_height, "tmp1" );
		if( img_handler.compare( curr_roi, base_roi ) ) _result += 10.0f;
	}

	if( _result == 160.0f ) return 999.0f;

	return _result;
}

Mat G_Jigsaw::select_individual() {

	float _slice = (float)(RANDOM_NUM * total_fitness);
	float curr_fitness = 0.0f;

	for( int i = 0; i < POPULATION_SIZE; i++ ) {
		curr_fitness += _population[i]._fitness;
		if( curr_fitness >= _slice ) {
			return _population[i]._solution;
		}
	}

	return img_handler.create_empty_img( 10, 10, "empty" );
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

