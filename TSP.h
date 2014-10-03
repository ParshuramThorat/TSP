

#ifndef TSP_H
#define TSP_H 

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
int  myrandom(int index) ;
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
Population* createPopulation(int populationSize , bool initilize);

int* getFittest(Population* pop , int populationSize);

int* getTour(Population* pop , int index); 

void setTour(Population* pop ,int* tour , int index);


int* tournamentSelection(Population* pop , int populationSize , int tournamentSize );

Population* evolvePopulation(Population* pop ,int populationSize,int tournamentSize , double mutationRate);

int* crossover(int * parent1 , int* parent2);

void mutate(int* tour , double mutationRate) ;

#endif // TSP_H