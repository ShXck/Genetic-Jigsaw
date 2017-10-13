#ifndef GJIGSAW_H_
#define GJIGSAW_H_

#define POPULATION_SIZE 10
#define CROSSOVER_RATE 0.7
#define MUTATION_RATE 0.001
#define MAX_GENERATIONS 400
#define RANDOM_NUM ((float)rand()/(RAND_MAX+1))

#include "ImageHandler.h"
#include "util.h"

typedef std::vector<std::pair<int,int>> Coords;
typedef std::pair<int,int> coord;

struct Individual {
	Mat _solution;
	float _fitness;
	Coords s_genes;  // positions that match the original image.
	Individual( Mat sol, float ftnss ) : _solution( sol ), _fitness( ftnss ) {}
};

typedef std::vector<Individual> Population;

class G_Jigsaw {
public:
	G_Jigsaw();
	G_Jigsaw( Image_Handler m_handler );
	void run();
	void restart();
	int fitness_of( Mat individual, Coords& s_genes );
	Image_Handler& handler();
	virtual ~G_Jigsaw();
private:
	void start_population( );
	void evolve();
	Individual select_individual();
	void crossover( Individual& img1, Individual& img2 );
	void mutate( Individual& individual );
private:
	Image_Handler img_handler;
	Population _population;
	float total_fitness;
	unsigned int current_generation;
	Individual* final_solution;
};

#endif /* GJIGSAW_H_ */
