#ifndef JIGSAW_H_
#define JIGSAW_H_

#define POPULATION_SIZE 20
#define CROSSOVER_RATE 0.95
#define MUTATION_RATE 0.009
#define MAX_GENERATIONS 1000

#include "ImageHandler.h"
#include "util.h"
#include <future>

typedef std::vector<std::pair<int,int>> Coords;
typedef std::pair<int,int> coord;

struct Individual {
	Mat _solution;
	float _fitness;
	Individual( Mat sol, float ftnss ) : _solution( sol ), _fitness( ftnss ) {}
};

typedef std::vector<Individual> Population;

class Jigsaw {
public:
	Jigsaw();
	Jigsaw( Image_Handler m_handler );
	void start_population( );
	void run();
	void pause();
	void stop();
	void continue_run();
	void restart();
	const bool& is_paused() const;
	const bool& is_running() const;
	const bool& is_stopped() const;
	unsigned int generation();
	Image_Handler& handler();
	virtual ~Jigsaw();
private:
	void evolve();
	int fitness_of( Mat individual );
	Individual select_individual();
	Individual crossover( Individual& img1, Individual& img2 );
	void mutate( Individual& individual );
	void update_sols();
	void set_fittest();
private:
	Image_Handler img_handler;
	Population _population;
	//Population _fittest;
	float total_fitness;
	unsigned int current_generation;
	Individual* final_solution;
	float goal_ftn;
	bool _paused = false;
	bool _running = false;
	bool _stopped = true;
};

#endif /* JIGSAW_H_ */
