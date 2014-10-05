

#ifndef TSP_H
#define TSP_H 

#define TOURNAMENT_SIZE 5
#define POPULATION_SIZE 50
#define ELITISISM true
#define MUTATE_RATE 0.015 
#define GENERATIONS 100


extern double** matrix ;
extern int noOfCities  ;

//Structure for city co-ordinates
typedef struct City_ {
	double x ;
	double y ;
	int rank;
}City ;

class Population{
public:	
	int * tour ;
};

/***********Create random number**********/
int* shuffleTour(int* tour) ;

/***********Create a Random Tour**********/
int* defaultTour();

/******print Tour*********/
void printTour(int* tour);

void setCity(int* tour , int index , int city);

double getCost(int* tour);

double getFitness(int* tour);

bool containsCity(int* tour , int city);

/*************creating population ******/
Population* createPopulation(int size,bool initilize);

int* getFittest(Population* pop, int size );

int* getTour(Population* pop , int index); 

void setTour(Population* pop ,int* tour , int index);


int* tournamentSelection(Population* pop );

Population* evolvePopulation(Population* pop );

int* crossover(int * parent1 , int* parent2);

void mutate(int* tour ) ;

#endif // TSP_H