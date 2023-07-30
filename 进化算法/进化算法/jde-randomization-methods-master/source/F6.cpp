#include "F6.h"

#include <fstream>
#include <iostream>

F6::F6(uint _dim):Benchmarks()
{
  n_dim = _dim;

  ID = 6;
  x_min = -32;
  x_max = +32;
}

F6::~F6(){
  /* empty */
}

double F6::compute(const vDouble gen, const uint ip){
  	/* Defining fitness function - Ackley function 
	   Dimensions: d
	   Domain: x ∈ [-32, 32]
	   Global minimum: (0, ..., 0)
	*/	

	double result = 0.0, aux = 0.0, aux1 = 0.0;
	
	for (uint i = 0; i < n_dim; i++){
    aux += gen[i + ip]*gen[i + ip];
  }

  for (uint i = 0; i < n_dim; i++){
    aux1 += cos(2.0*M_PI*gen[i + ip]);
  }

  result = (-20.0*(exp(-0.2*sqrt(1.0/(float)n_dim*aux)))-exp(1.0/(float)n_dim*aux1)+20.0+exp(1));

  return result;
}

