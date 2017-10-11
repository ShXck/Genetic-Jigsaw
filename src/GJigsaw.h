#ifndef GJIGSAW_H_
#define GJIGSAW_H_

#define POPULATION_SIZE 10
#define CROSSOVER_RATE 0.7
#define MUTATION_RATE 0.001
#define MAX_GENERATIONS 400
#define RANDOM_NUM ((float)rand()/(RAND_MAX+1))

#include "ImageHandler.h"
#include "util.h"

struct Individual {
	Mat _solution;
	float _fitness;
	Individual( Mat sol, float ftnss ) : _solution( sol ), _fitness( ftnss ) {}
};

typedef std::vector<Individual> Population;

class G_Jigsaw {
public:
	G_Jigsaw();
	void run();
	void restart();
	virtual ~G_Jigsaw();
private:
	void evolve();
	void start_population( );
	void generate_population( int n_individual );
	int fitness_of( Mat individual );
	Mat select_individual();
	void crossover( Mat& img1, Mat& img2 );
	void mutate( Mat& individual );
private:
	Image_Handler m_handler;
	Population _population;
	Individual* final_solution;
	float total_fitness;
	unsigned int current_generation;
};

#endif /* GJIGSAW_H_ */
