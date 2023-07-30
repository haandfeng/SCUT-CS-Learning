#include "F2.h"

#include <fstream>
#include <iostream>

F2::F2(uint _dim):Benchmarks()
{
  n_dim = _dim;

  ID = 2;
  x_min = -5.12;
  x_max = +5.12;
}

F2::~F2(){
  /* empty */
}

double F2::compute(const vDouble gen, const uint ip){
  	/* Defining fitness function - Rastrigin's function 
	   Dimensions: d
	   Domain: x ∈ [-5.12, 5.12]
	   Global minimum: (0, ..., 0)
	*/
	double result = 0;

	for(uint i = 0; i < n_dim; i++) {
        result += pow(gen[i + ip], 2.0) - 10 * cos(2 * M_PI * gen[i + ip]) + 10;
    }

    return result;
}

