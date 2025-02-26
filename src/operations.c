#include "operations.h"
#include <stdio.h>
#include <math.h>


int prod(int x, int y){
		
	if(x == 0) 
	{
		return 0;
	}
	
	int prod = 1;
	
	for(int i = x; i <= y; i++)
	{
		prod *= i; 
	}
	
	return prod;
};

int fib(int x){ 

	if(x <= 1) 
	{
		return x;
	}
	
	return fib(x - 1) + fib(x - 2); 
};

int power(int x, int y){
	
	int z = pow(x, y);
	
	return z;
};

int sum(int x, int y){
	
	int z = x + y;
	return z;
};
