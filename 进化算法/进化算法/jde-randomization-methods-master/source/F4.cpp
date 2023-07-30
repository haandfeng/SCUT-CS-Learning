#include "F4.h"

#include <fstream>
#include <iostream>

F4::F4(uint _dim):Benchmarks()
{
  n_dim = _dim;

  ID = 4;
  x_min = -5.0;
  x_max = +10.0;
}

F4::~F4(){
  /* empty */
}

double F4::compute(const vDouble gen, const uint ip){
  	/* Defining fitness function - Rosenbrock's function 
	   Dimensions: d
	   Domain: x ∈ [-5, 10]
	   Global minimum: (1, ..., 1)
	*/	

	double result = 0.0;
	
	for(uint i = 0; i < n_dim-1; i++) {
        result += 100.0 * pow((gen[i+1 + ip] - pow(gen[i + ip],2.0)),2) + pow((1.0 - gen[i + ip]),2);
    }

    return result;
}

