#include "Jigsaw.h"
#include <random>

Jigsaw::Jigsaw( ) : total_fitness( 0.0f ), current_generation( 0 ), final_solution( nullptr ) {
	 goal_ftn = img_handler.img_details().total_parts * 10.f;
}

Jigsaw::Jigsaw( Image_Handler m_handler ) : total_fitness( 0.0f ), current_generation( 0 ), final_solution( nullptr ) {
	img_handler = m_handler;
	goal_ftn = img_handler.img_details().total_parts * 10.f;
}

void Jigsaw::run() {

	_running = true;
	_stopped = false;

	bool _found = false;

	while( !_found && !_stopped ) {

		if( _running && !_paused ) {

			total_fitness = 0.0f;

			for( int i = 0; i < POPULATION_SIZE; i++ ) {
				Individual& curr = _population[i];
				curr._fitness = fitness_of( curr._solution  );
				total_fitness += curr._fitness;
			}

			for( int i = 0; i < POPULATION_SIZE; i++ ) {
				Individual& curr = _population[i];
				if( curr._fitness == 999.0f ) {
					std::cout << "SOLUTION FOUND!" <<  "GENERATION: " << current_generation <<  std::endl;
					final_solution = &curr;
					img_handler.create_img( "fit0.jpg", final_solution->_solution );
					_found = true;
					break;
				}
			}

			evolve();

			if( current_generation > MAX_GENERATIONS ) {
				std::cout << "NO SOLUTION FOUND THIS RUN!" << std::endl;
				_found = true;
			}
			set_fittest();
		}
	}
	set_fittest();
	update_sols();
}

void Jigsaw::evolve() {

	Population tmp_pop;

	int pop_ctr = 0;

	while( pop_ctr < POPULATION_SIZE ) {

		Individual ind_1 = select_individual();
		Individual ind_2 = select_individual();

		Individual _offspring = crossover( ind_1, ind_2 );

		mutate( _offspring );

		tmp_pop.push_back( _offspring );

		pop_ctr++;
	}

	for( int i = 0; i < POPULATION_SIZE; i++ ) {
		_population[i] = tmp_pop[i];
	}

	++current_generation;
}

void Jigsaw::start_population() {
	Mat r;
	for( int i = 0; i < POPULATION_SIZE; i++ ) {
		r = img_handler.join_parts();
		img_handler.create_img( "sol" +  std::to_string( i ) + ".jpg", r );
		_population.push_back( Individual( r, 0.0f ) );
	}
}

int Jigsaw::fitness_of( Mat individual ) {

	Coords& _coords = img_handler.coords();
	float _result = 0.0f;

	Mat& _base = img_handler.base();

	for( unsigned int i = 0; i < _coords.size(); i++ ) {
		auto c = _coords[i];
		Mat curr_roi = img_handler.crop( individual, c.first, c.second, img_handler.img_details().parts_width, img_handler.img_details().parts_height, "tmp" );
		Mat base_roi = img_handler.crop( _base , c.first, c.second, img_handler.img_details().parts_width, img_handler.img_details().parts_height, "tmp1" );
		if( img_handler.compare( curr_roi, base_roi ) ) {
			_result += 10.0f;
		}
	}

	if( _result == goal_ftn ) return 999.0f;

	return _result;
}

Individual Jigsaw::select_individual() {

	float _slice = (float)( util::random_float( 0, 1 ) * total_fitness );
	float curr_fitness = 0.0f;

	for( int i = 0; i < POPULATION_SIZE; i++ ) {
		curr_fitness += _population[i]._fitness;
		if( curr_fitness >= _slice ) {
			return _population[i];
		}
	}
	return _population[0];
}

Individual Jigsaw::crossover( Individual& img1, Individual& img2 ) {

	Coords& _coords = img_handler.coords();

	if( util::random_float( 0, 1 ) < CROSSOVER_RATE ) {

		unsigned int crossover_point = int( util::random_float( 0, 1 ) * _coords.size() );

		Mat new_ind = img_handler.create_empty_img( "offspring" );

		//Copia los elementos del primer individuo hasta el punto de cruce
		for( unsigned int i = 0; i < crossover_point; i++ ) {
			auto curr = _coords[i];
			Mat _piece = img_handler.crop( img1._solution, curr.first, curr.second, img_handler.img_details().parts_width, img_handler.img_details().parts_height );
			img_handler.join( new_ind, _piece, curr.first, curr.second );
		}

		Coords _blanks;

		//Copia los elementos del segundo padre del punto de cruce en adelante.
		for( unsigned int i = crossover_point; i < _coords.size(); i++ ) {
			auto curr = _coords[i];
			Mat _piece = img_handler.crop( img2._solution, curr.first, curr.second, img_handler.img_details().parts_width, img_handler.img_details().parts_height );
			if( !img_handler.contains( new_ind, _piece ) ) img_handler.join( new_ind, _piece, curr.first, curr.second );
			else _blanks.push_back( curr );
		}

		int blank_index = 0;
		//Copia los elementos faltantes del primer padre
		for( auto coord : _coords ) {
			Mat _piece = img_handler.crop( img1._solution, coord.first, coord.second, img_handler.img_details().parts_width, img_handler.img_details().parts_height );
			if( !img_handler.contains( new_ind, _piece ) ) {
				img_handler.join( new_ind, _piece, _blanks[blank_index].first, _blanks[blank_index].second );
				blank_index++;
			}
		}
		return Individual( new_ind, 0.0f );
	}
	return img1;
}

void Jigsaw::mutate( Individual& individual ) {

	int _width = img_handler.img_details().parts_width;
	int _height = img_handler.img_details().parts_height;
	Coords& _coords = img_handler.coords();
	int _lim = std::sqrt( img_handler.img_details().total_parts ) - 1;

	for( unsigned int i = 0; i < _coords.size(); i++ ) {
		if( util::random_float( 0, 1 ) < MUTATION_RATE ) {
			coord mut_from( _width * util::random_int( 0, _lim ), _height * util::random_int( 0, _lim ) );
			coord mut_to( _width * util::random_int( 0, _lim ), _height * util::random_int( 0, _lim ) );
			img_handler.switch_parts( mut_from, mut_to, individual._solution );
		}
	}
}

void Jigsaw::restart() {
	_population.clear();
	total_fitness = 0.0f;
	current_generation = 0;
}

void Jigsaw::update_sols() {
	while( !_stopped ) {
		std::this_thread::sleep_for( std::chrono::seconds( 6 ) );
		for( unsigned int i = 0; i < _population.size(); i++ ) {
			img_handler.create_img( "sol" + std::to_string( i ) + ".jpg", _population[i]._solution );
		}
	}
}

void Jigsaw::set_fittest() {

	int _first, _second, _third;

	_first = _second = _third = INT_MIN;

	for( unsigned int i = 0; i < _population.size(); i++ ) {
		if( (int)_population[i]._fitness > _first ) {
			_third = _second;
			_second = _first;
			_first = i;
		} else if( (int)_population[i]._fitness > _second ) {
			_third = _second;
			_second = i;
		} else if( (int)_population[i]._fitness > _third ) {
			_third = i;
		}
	}

	 img_handler.create_img( "fit0.jpg", _population[_first]._solution );
	 img_handler.create_img( "fit1.jpg", _population[_second]._solution );
	 img_handler.create_img( "fit2.jpg", _population[_third]._solution );
}

void Jigsaw::pause() {
	_paused = true;
	_running = false;
}

void Jigsaw::stop() {
	_stopped = true;
	_running = false;
	_paused = false;
}

void Jigsaw::continue_run() {
	_running = true;
	_paused = false;
}

const bool& Jigsaw::is_paused() const {
	return _paused;
}

const bool& Jigsaw::is_running() const {
	return _running;
}

const bool& Jigsaw::is_stopped() const {
	return _stopped;
}

unsigned int Jigsaw::generation() {
	return current_generation;
}

Image_Handler& Jigsaw::handler() {
	return img_handler;
}

Jigsaw::~Jigsaw() { }

