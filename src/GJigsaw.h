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
typedef std::vector<std::pair<int,int>> Coords;

class G_Jigsaw {
public:
	G_Jigsaw();
	void run();
	void restart();
	virtual ~G_Jigsaw();
private:
	void start_population( );
	void evolve();
	int fitness_of( Mat individual );
	Mat select_individual();
	void crossover( Mat& img1, Mat& img2 );
	void mutate( Mat& individual );
private:
	Image_Handler img_handler;
	Population _population;
	float total_fitness;
	unsigned int current_generation;
	Individual* final_solution;
};

#endif /* GJIGSAW_H_ */
