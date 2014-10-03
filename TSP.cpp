#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <ctime>
#include "TSP.h"

using namespace std ;

/***********For Tour*********/
int myrandom(int index )
{
	srand( time(0) ) ;
	return rand() % index ;
}
int* shuffleTour(int* tour)
{
	random_shuffle ( tour, tour+noOfCities-1 , myrandom );
	return tour ;
}

int* defaultTour()
{
	int * tempTour ;
	tempTour = new int [noOfCities] ;
	for (int i = 0; i < noOfCities; ++i)
	{
		tempTour[i] = i+1 ;	
	}
	return tempTour ;
}

void printTour(int* tour)
{
	for (int i = 0; i < noOfCities; ++i){
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
	double cost = 10000.0 ;
	return cost ;	
}

double getFitness(int* tour)
{
	return 1/(double)getCost(tour);
}

bool containsCity(int* tour , int city)
{
	for (int i = 0; i < noOfCities; ++i)
	{
		if( tour[i] == city ) return true ;
	}
	return false;
}

/*************creating population ******/
Population* createPopulation(int populationSize , bool initialize)
{
		
	Population* pop ;
	pop = new Population[populationSize];
	if(initialize)
	{	
		int* tempTour ;
		tempTour = defaultTour();

		for (int i = 0; i < populationSize; ++i)
		{	
			pop[i].tour = shuffleTour(tempTour) ;
			tempTour = pop[i].tour ;		
		}
	
	}
	return pop ;
}

/************get Tour from population*********/
int* getTour(Population* pop , int index)
{
	return pop[index].tour ;
}

/************get fittest tour of the population***********/
int* getFittest(Population* pop , int populationSize)
{
	int* fittest = pop[0].tour ;
	for (int i = 0; i < populationSize; ++i)
	{
		if( getFitness(fittest) < getFitness(pop[i].tour) )
			fittest = pop[i].tour ;	
	}
	return fittest ;
}
/****************set tour in population************/
void setTour(Population* pop ,int* tour , int index)
{
	pop[index].tour = tour ;
}


/***************GA*************/
void mutate(int* tour , double mutationRate)
{
		if( ( (double)rand() / (double)RAND_MAX ) < mutationRate)
		{
			int tourIndex1 = rand() % noOfCities ;
			int tourIndex2 = rand() % noOfCities ;
			
			int city1 = tour[ tourIndex1 ];
			int city2 = tour[ tourIndex2 ] ;
			
			setCity(tour , tourIndex2 , city1);
			setCity(tour , tourIndex1 , city2) ;
		}
}


int* crossover(int * parent1 , int* parent2)
{
	int* child ;
	child = new int[noOfCities] ;
	int startPos = rand() % noOfCities ;
	int endPos = rand() % noOfCities ;

	for (int i = 0; i < noOfCities; ++i)
	{	child[i] = 0 ;
		if (startPos < endPos && i > startPos && i < endPos)
		{
			setCity(child ,i, parent1[i]);
		}
		else if (startPos > endPos)
		{
			if (!(i > startPos && i < endPos))
			{
				setCity(child , i ,parent1[i] );
			}
		}
	}
	for (int i = 0; i < noOfCities; ++i)
	{
		if ( !containsCity( child , parent2[i] ) )
		{
			for (int ii = 0; ii < noOfCities; ++ii)
			{
				if(child[i] == 0)
				{
					child[i] = parent2[i] ;
					break ;
				}
			}
		}
	}
}

Population* evolvePopulation(Population* pop ,int populationSize,int tournamentSize , double mutationRate)
{
	bool elitism = true ;
	int elitismOffset = 0 ;
	Population* newPopulation ;
	newPopulation = createPopulation(populationSize , false);
	if(elitism)
	{
		setTour(newPopulation , getFittest(pop , populationSize) , elitismOffset ) ;
		elitismOffset++ ;
	}
		// Crossover population
        // Loop over the new population's size and create individuals from
        // Current population
	for (int i = elitismOffset; i < populationSize; ++i)
	{
		int* parent1 = tournamentSelection(pop , populationSize ,tournamentSize);
		int* parent2 = tournamentSelection(pop , populationSize ,tournamentSize) ;
		
		int* child = crossover(parent1 , parent2);
		setTour(newPopulation , child , i);	
	}
	 // Mutate the new population a bit to add some new genetic material
    for (int i = elitismOffset; i < populationSize; i++)
    {
        mutate( getTour(newPopulation , i) , mutationRate);
    }

    return newPopulation;

}



int* tournamentSelection(Population* pop , int populationSize , int tournamentSize )
{
	Population* tournament ;
	tournament = createPopulation(tournamentSize , false);
	for (int i = 0; i < tournamentSize; ++i)
	 {
	 	int randomId = rand() % populationSize ;
	 	printf("randomId = %d\n", randomId);
	 	setTour(tournament , pop[randomId].tour , i) ;
	 	printTour(tournament[i].tour);
	 }

	 return getFittest(tournament , tournamentSize); 
}