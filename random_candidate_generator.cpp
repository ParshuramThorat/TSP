#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <cstdlib>      // std::rand, std::srand

int myrandom (int i) { return std::rand()%i;}
int* random_cand_gen(int i, int no_Of_Cities) {
	std::srand ( i );
 	int * tour;
  	tour = (int*)malloc(no_Of_Cities*sizeof(int));
  	for (int j=0; j<no_Of_Cities; ++j) tour[j]=j+1;
  	std::random_shuffle ( tour, tour+no_Of_Cities-1,myrandom );
	return tour;
}