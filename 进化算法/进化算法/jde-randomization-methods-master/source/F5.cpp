#include "F5.h"

#include <fstream>
#include <iostream>

F5::F5(uint _dim):Benchmarks()
{
  n_dim = _dim;

  ID = 5;
  x_min = -5.12;
  x_max = +5.12;
}

F5::~F5(){
  /* empty */
}

double F5::compute(const vDouble gen, const uint ip){
  	/* Defining fitness function - Sphere function 
	   Dimensions: d
	   Domain: x ∈ [-5.12, 5.12]
	   Global minimum: (0, ..., 0)
	*/	

	double result = 0.0;
	
	for(uint i = 0; i < n_dim; i++) {
        result += pow(gen[i + ip],2);
    }

    return result;
}

