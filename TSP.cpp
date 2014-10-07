#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <time.h>

#include "TSP.h"

using namespace std ;

int* shuffleTour(int* tour)
{	
	random_shuffle ( &tour[1], &tour[noOfCities]+1);
	return tour ;
}

int* defaultTour()
{
	int * tempTour ;
	tempTour = new int [noOfCities+1] ;
	for (int i = 1; i <= noOfCities; ++i)
	{
		tempTour[i] = i ;	
	}
	return tempTour ;
}

void printTour(int* tour)
{
	for (int i = 1; i <= noOfCities; ++i){
		printf("%d, ", tour[i]);
	}
	printf("\n");
}

void setCity(int* tour, int index, int city)
{
	tour[index] = city ;
}

double getCost(int* tour)
{
	double cost = 0.0;
	for (int i = 1; i <noOfCities; ++i)
	{
		cost += matrix[ tour[i] ][ tour[i+1] ];
	}
		cost += matrix[ tour[noOfCities] ][ tour[1] ] ;
	return cost ;	
}

double getFitness(int* tour)
{
	return 1/(double)getCost(tour);
}

bool containsCity(int* tour , int city)
{
	for (int i = 1; i <= noOfCities; ++i)
	{
		if( tour[i] == city ) return true ;
	}
	return false;
}
void swapCity(int* tour , int cityIndex1 , int cityIndex2){
		
		int temp = tour[ cityIndex1 ] ;
		tour[ cityIndex1 ] = tour[ cityIndex2 ] ;
		tour[ cityIndex2 ] = temp ;		
		//return tour ;
}
/*************creating population ******/
Population* createPopulation(int size , bool initialize)
{
		
	Population* pop ;
	pop = new Population[size];
	int worstIndex;   
	int worstCost ;
	int city;
    int * nextRandomTour ; 		
	if(initialize){
		for (int i = 0; i < RANDOM_MAX ; ++i)
		{	
			//printf("count = %d\n",i );
			city = rand() % (noOfCities-1) + 1;
			if( i < size)
			{
				pop[i].tour = nearestNeighbourTour(city);				
			}
			else
			{	

				worstIndex  = getWeakestIndex(pop , size);  
				worstCost   = getCost(pop[worstIndex].tour);
				
				nextRandomTour = nearestNeighbourTour(city);
				if( getCost( nextRandomTour ) < worstCost ){
					pop[worstIndex].tour = nextRandomTour;
				}
			}

		}
	}
	return pop ;
}

/**************nearest neibour ************/
int nearestNeighbour(int* tour , int* visited , int city)
{
	int costOFEdge = 10000000  ;
	int nearest_Neighbour ;
	for (int i = 1; i <= noOfCities; ++i)
	{
		if ( visited[i] == 0 && matrix[city][i] < costOFEdge )
		{
			nearest_Neighbour = i ;
			costOFEdge = matrix[city][i] ;
		}	
	}
	return nearest_Neighbour ;
} 

/*************nearest neighbour tour**********/
int* nearestNeighbourTour(int city)
{
	int* tour ;
	int * visited ;
	tour = new int [noOfCities+1] ;
	visited = new int [noOfCities+1] ; 
	for (int i = 1; i <= noOfCities; ++i)
	{
		tour[i] = 0 ;
		visited[i] = 0;
	}
	
	tour[1] = city ;
	visited[city] = 1 ;
	for (int i = 2; i <= noOfCities; ++i)
	{
		tour[i] = nearestNeighbour(tour , visited , city);
		city = tour[i] ;
		visited[city] = 1 ;
	}
	return tour ;
}


/************get Tour from population*********/
int* getTour(Population* pop , int index)
{
	return pop[index].tour ;
}

/****************set tour in population************/
void setTour(Population* pop ,int* tour , int index)
{
	pop[index].tour = tour ;
}

/************get fittest tour of the population***********/
int* getFittest(Population* pop , int size )
{
	int* fittest = pop[0].tour ;
	for (int i = 0; i < size; ++i)
	{
		if( getFitness(fittest) < getFitness(pop[i].tour) )
			fittest = pop[i].tour ;	
	}
	return fittest ;
}
/************getweakest tour index in the population***********/
int getWeakestIndex(Population* pop, int size)
{
	int* weakest = pop[0].tour ;
	int index = 0 ;
	for (int i = 0; i < size; ++i)
	{
	 	if( getCost(weakest) < getCost(pop[i].tour) ){
	 		weakest = pop[i].tour ;
	 		index = i ;
	 	}
	} 
	return index ;	
}

/***************GA*************/
void mutate(int* tour )
{	
			
		if( ( (double)rand() / (double)RAND_MAX ) < MUTATE_RATE)
		{
			int tourIndex1 = rand() % (noOfCities-1) +1 ;
			int tourIndex2 = rand() % (noOfCities-1) +1;
		
			int city1 = tour[ tourIndex1 ];
			int city2 = tour[ tourIndex2 ] ;
			
			setCity(tour , tourIndex2 , city1);
			setCity(tour , tourIndex1 , city2) ;
		}
}


int* crossover(int * parent1 , int* parent2)
{
	int* child ;
	child = new int [noOfCities+1] ;
	int startPos = rand() % (noOfCities-1) +1;
	int endPos   = rand() % (noOfCities-1) +1 ;
	if (startPos > endPos)
	{
		int temp = startPos ;
		startPos = endPos ;
		endPos = temp ;
	}

	//printf("startPos = %d , endPos = %d\n" , startPos , endPos);	
	
	for (int i = 1; i <= noOfCities; ++i)
	{	child[i] = 0 ;
		if (i >= startPos && i <= endPos)
			setCity(child ,i, parent1[i]);		
	}

	for (int i = 1; i <= noOfCities; ++i)
	{
		if ( !containsCity( child, parent2[i] ) )
		{
			for (int ii = 1; ii <= noOfCities; ++ii)
			{
				if(child[ii] == 0)
				{
					child[ii] = parent2[i] ;
					ii = noOfCities+1;
				}
			}
		}
	}
	return child ;
}

Population* evolvePopulation(Population* pop)
{
	int elitismOffset = 0 ;
	Population* newPopulation ;
	newPopulation = createPopulation(POPULATION_SIZE ,false);
	if(ELITISISM)
	{
		setTour(newPopulation , getFittest(pop , POPULATION_SIZE) , 0 ) ;
		elitismOffset = 1;
	}
		// Crossover population
        // Loop over the new population's size and create individuals from
        // Current population
	for (int i = elitismOffset; i < POPULATION_SIZE; ++i)
	{
		int* parent1 = tournamentSelection(pop );
		int* parent2 = tournamentSelection(pop );
		
		int* child = crossover(parent1 , parent2);
		setTour(newPopulation , child , i);	
	}
	 // Mutate the new population a bit to add some new genetic material
    for (int i = elitismOffset; i < POPULATION_SIZE; i++)
    {
        mutate( getTour(newPopulation , i) );
    }
    return newPopulation;

}



int* tournamentSelection(Population* pop )
{
	Population* tournament ;
	tournament = createPopulation(TOURNAMENT_SIZE,false);
	for (int i = 0; i < TOURNAMENT_SIZE; ++i)
	{
	 	int randomId = rand() % (POPULATION_SIZE-1) + 1 ;
	 	setTour(tournament , pop[randomId].tour , i) ;
	}
	 int * temp = getFittest(tournament , TOURNAMENT_SIZE);  
	 free(tournament);
	 return temp; 
}

int* optimizer(int* tour){
	printf("after optimizer\n" );
	int tourCost = getCost(tour); 
	for (int i = 1; i <= noOfCities; ++i)
	{
		for (int j = 1; j <= noOfCities; ++j)
		{
			swapCity(tour, i , j );
			if( tourCost < getCost(tour) )
			{
				swapCity(tour, j , i );
			}else{
				return tour;
				//tourCost = getCost(tour);
			}	
		}
	}
	return tour ;
}
