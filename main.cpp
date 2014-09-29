/*
Authors : Parshuram Thorat(CS12B056); Sai Sanketh B K(CS12B026)
Date   : 24  September 2014  
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "evaluator.cpp"
#include "random_candidate_generator.cpp"

//Structure for city co-ordinates
typedef struct City{
	long double x ;
	long double y ;
	int rank;
}city ;

int main(){
	int no_Of_Cities ;
	char type[100] ;
	city * cities ;       // Array of struct "City"
	long double ** matrix ;
	
	scanf("%s" , type) ;
	scanf("%d" , &no_Of_Cities) ;
	int * tour = (int*)malloc(no_Of_Cities*sizeof(int));
	
	cities = (city*)malloc(sizeof(city)*no_Of_Cities);
	
	matrix = new long double* [no_Of_Cities] ;
		for (int i = 0; i < no_Of_Cities; ++i) {
			matrix[i] = new long double[no_Of_Cities] ;
	}
	
	for (int i = 0; i < no_Of_Cities; ++i)
	{
		scanf("%Lf %Lf" , &cities[i].x , &cities[i].y);
	}
	for (int i = 0; i < no_Of_Cities; ++i) {	
		for (int j = 0; j < no_Of_Cities; ++j) {
			scanf("%Lf" , &matrix[i][j]);
		}	
	}
	for (int i = 0; i < 50; ++i)
	{
	tour= random_cand_gen(i,no_Of_Cities);
	long double cost = evaluator(matrix,no_Of_Cities,tour);
	// for (int i = 0; i < no_Of_Cities; ++i)
	// {
	// 	printf("%d ",tour[i] );
	// }
	printf("%Lf\n",cost );
	}
	return 0 ;
}