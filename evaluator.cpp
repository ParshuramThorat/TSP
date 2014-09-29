#include<iostream>
long double evaluator(long double ** matrix,int no_Of_Cities,int* visited_order )
{
	long double cost=0;
	for (int i = 0; i < no_Of_Cities-1; ++i)
	{
		cost += matrix[visited_order[i]-1][visited_order[i+1]-1];
	}
	cost+=matrix[visited_order[no_Of_Cities-1]-1][visited_order[0]-1];
	return cost;
}