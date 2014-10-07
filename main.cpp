/*
Authors : Parshuram Thorat(CS12B056); Sai Sanketh B K(CS12B026)
Date   : 24  September 2014  
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <unistd.h>
#include "TSP.h"

using namespace std ;

double** matrix ;
int noOfCities  ;

double optimizedCost  ;
int* optimizedTour ;

int main(){
	srand(time(0));
	int seconds = 0 ;		
	clock_t t1,t2 ;
    
    t1 = clock();
    
	char type[20] ;
	City * cities ;       // Array of struct "City"

	scanf("%s" , type) ;
	scanf("%d" , &noOfCities) ;
	
	cities = (City*)malloc(sizeof(City)*(noOfCities+1) );
	
	matrix = new double* [noOfCities+1] ;
		for (int i = 0; i <= noOfCities; ++i) {
			matrix[i] = new double [noOfCities+1] ;
	}
	
	for (int i = 1; i <= noOfCities; ++i) {
		scanf("%lf %lf" , &cities[i].x , &cities[i].y);
	}
	for (int i = 1; i <= noOfCities; ++i) {	
		for (int j = 1; j <= noOfCities; ++j) {
			scanf("%lf" , &matrix[i][j]);
		}	
	}	
	
	Population *pop ;	
	pop = createPopulation(POPULATION_SIZE ,true);
    
	optimizedCost = getCost(getFittest(pop , POPULATION_SIZE));
	double currentCost = optimizedCost ;
	    
	printf("Initial Cost = %lf\n", optimizedCost );
	
	do{
		
		for (int i = 0; i < GENERATIONS; ++i)
		{
			pop = evolvePopulation( pop);
		}
	    
	    optimizedTour = getFittest(pop , POPULATION_SIZE) ;
	    currentCost   = getCost(optimizedTour) ;
	    if (optimizedCost > currentCost)
		{
			optimizedCost = currentCost ;	
			printf("Cost = %lf\n", optimizedCost );			
			printTour(optimizedTour) ;

		}
		//else printf("%d\n", count );
		t2 = clock();
    	float diff ((float)t2-(float)t1);    
    	seconds = diff / CLOCKS_PER_SEC;
		//printf("Time taken = %d\n", seconds );
	
		//code goes here
	}while(seconds <= 5*60-2 );

	printf("Final Cost = %lf\n", optimizedCost );
	printTour(optimizedTour) ;
	
	return 0 ;
}