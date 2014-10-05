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

/*************creating population ******/
Population* createPopulation(int size , bool initialize)
{
		
	Population* pop ;
	pop = new Population[size];
	if(initialize) 
		for (int i = 0; i < size ; ++i) 
			pop[i].tour = shuffleTour(defaultTour()) ;
	
	return pop ;
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

/***************GA*************/
void mutate(int* tour )
{	
			
		if( ( (double)rand() / (double)RAND_MAX ) < MUTATE_RATE)
		{
			int tourIndex1 = rand() % (noOfCities-1) +1 ;
			int tourIndex2 = rand() % (noOfCities-1) +1;
			
			if (tourIndex1 == 0 || tourIndex2 == 0)
			{
				printf("tourIndex1 = 0 \n");	
				exit(0);
			}

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
	int endPos   = rand() % (noOfCities-1)+1 ;
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
		setTour(newPopulation , getFittest(pop , POPULATION_SIZE) , elitismOffset ) ;
		elitismOffset++ ;
	}
		// Crossover population
        // Loop over the new population's size and create individuals from
        // Current population
	for (int i = elitismOffset; i < POPULATION_SIZE; ++i)
	{
		int* parent1 = tournamentSelection(pop );
		int* parent2 = tournamentSelection(pop ) ;
		
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

	 return getFittest(tournament , TOURNAMENT_SIZE); 
}