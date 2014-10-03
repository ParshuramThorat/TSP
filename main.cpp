/*
Authors : Parshuram Thorat(CS12B056); Sai Sanketh B K(CS12B026)
Date   : 24  September 2014  
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include "TSP.h"

#define POPULATION_SIZE 50
#define ELITISISM true
#define MUTATE_RATIO 0.15  

using namespace std ;

double** matrix ;
int noOfCities  ;

int main(){
	char type[20] ;
	City * cities ;       // Array of struct "City"

	scanf("%s" , type) ;
	scanf("%d" , &noOfCities) ;
	
	cities = (City*)malloc(sizeof(City)*noOfCities);
	
	matrix = new double* [noOfCities] ;
		for (int i = 0; i < noOfCities; ++i) {
			matrix[i] = new double [noOfCities] ;
	}
	
	for (int i = 0; i < noOfCities; ++i) {
		scanf("%lf %lf" , &cities[i].x , &cities[i].y);
	}
	for (int i = 0; i < noOfCities; ++i) {	
		for (int j = 0; j < noOfCities; ++j) {
			scanf("%lf" , &matrix[i][j]);
		}	
	}	

	Population *pop ;
	pop = createPopulation(10 , true);
	//printf("initial Distance = %lf\n", getCost( getFittest(pop, 10)  ));

	pop = evolvePopulation( pop ,10, 5 ,  0.015);

    // for (int i = 0; i < 1; i++) {
    //     pop = evolvePopulation(pop , 10 , 5 , 2);
    // }
	
	//printf("Cost = %lf\n", getCost( getFittest(pop , 10) ));
	//printTour( getFittest(pop , 10) ) ;
	
	return 0 ;
}