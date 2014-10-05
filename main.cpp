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

int optimizedCost = 0 ;
int* optimizedTour ;

int main(){
	clock_t t1,t2;
    t1 = clock();
    srand(time(NULL));
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
	int seconds ;	
	do{
		for (int i = 0; i < GENERATIONS; ++i)
		{
			pop = evolvePopulation( pop);
		}
	    
	    optimizedTour = getFittest(pop , POPULATION_SIZE) ;
	    printTour(optimizedTour) ;
		printf("Cost = %lf\n", getCost( optimizedTour ) );			
		
		//code goes here
	    t2 = clock();
    	float diff ((float)t2-(float)t1);    
    	seconds = diff / CLOCKS_PER_SEC;
	}while(seconds <= 5*60 );
	
	return 0 ;
}