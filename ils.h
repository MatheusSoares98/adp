#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <time.h>
#ifndef RAND_MAX
#define RAND_MAX = 10
#endif
#include "auxiliary.h"


void generate_random_positions(int size, int pos[4]) {
	int aux = 0, cursor = 0, counter = 0;
	bool unique = false;
	for (int i = 0; i < 4; )
	{
		aux = rand() % size;
		for (int j = 0; j < cursor || cursor == 0; j++, counter++)
		{
			if(cursor == 0){
				unique = true;
				break;
			}
			else if (aux == pos[j]) {
				break;
			}
			else if (aux == pos[j] + 1) {
				break;
			}
			else if(aux == pos[j] - 1){
				break;
			}
			else if(aux == 0 && pos[j] == size-1 || aux == size-1 && pos[j] == 0)
			{
				break;
			}
			else if (j == cursor - 1)
			{
				unique = true;
			}
		}
		if(unique == true || cursor == 0) {
			pos[i] = aux;	
			i++;
			cursor++;
		}
		if (counter > 10)
		{
			return generate_random_positions(size, pos);
		}
		unique = false;	
	}

}

void bubble_sort(int pos[4]) {
	int  n = 4, i, j, swap;
	bool flag = false;
	
	for(i = 0 ; i < n - 1; i++) {
		flag = false;
		for(j = 0 ; j < n-i-1; j++) {
			if(pos[j] > pos[j+1]) {
				swap = pos[j];
				pos[j] = pos[j+1];
				pos[j+1] = swap;
				flag = true;
			}
		}
		if(!flag) {
			break;
		}
	}
}


void create_successors_array(int numberOfCities, int pos[4], int successors[numberOfCities], int successorsCopy[numberOfCities]) {
	int aux;
	
	for (int i = 0; i < numberOfCities; ++i)
	{
		successors[i] = i + 1;
	}
	successors[numberOfCities-1] = 0;
	
	aux = successors[pos[0]];
	successors[pos[0]] = successors[pos[2]];
	successors[pos[2]] = aux;
	aux = successors[pos[1]];
	successors[pos[1]] = successors[pos[3]];
	successors[pos[3]] = aux;

}

void double_bridge(int numberOfCities, step path[numberOfCities]) {
	int pos[4] = {-3,-3, -3, -3};
	int successors[numberOfCities], successorsCopy[numberOfCities];
	step copy[numberOfCities];
	copy_path(numberOfCities, path, copy);
	city swap;
	generate_random_positions(9, pos);
	bubble_sort(pos);
	create_successors_array(numberOfCities, pos, successors, successorsCopy);
	swap = path[pos[0]].finish;
	path[pos[0]].finish = path[pos[2]].finish;
	path[pos[2]].finish = swap;

	swap = path[pos[1]].finish;
	path[pos[1]].finish = path[pos[3]].finish;
	path[pos[3]].finish = swap;

	for (int i = 0; i < numberOfCities; ++i)
	{
		successorsCopy[i] = successors[i];
	}
	copy[0]= path[0];
	
	for (int i = 1; i < numberOfCities; ++i)
	{
		copy[i] = path[successorsCopy[i-1]];
		successorsCopy[i] = successors[successorsCopy[i-1]];
	}

	copy_path(numberOfCities, copy, path);
}