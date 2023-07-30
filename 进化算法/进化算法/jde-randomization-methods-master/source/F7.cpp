#include "F7.h"

#include <fstream>
#include <iostream>

F7::F7(uint _dim):Benchmarks()
{
  n_dim = _dim;

  ID = 7;
  x_min = -500;
  x_max = +500;
}

F7::~F7(){
  /* empty */
}


double F7::compute(const vDouble gen, const uint ip){
  	/* Defining fitness function - Schwefel function 
	   Dimensions: d
	   Domain: x ∈ [-500, 500]
	   known_optimal = -418.982887272433 at  sol(i)=420.9687
	*/	

  double result = 0.0, aux = 0.0;

  for (uint i = 0; i < n_dim; i++){
    aux += gen[i + ip] * sin(sqrt(fabs(gen[i + ip]))); 
  }

  result = (-1*aux/n_dim);

  return result;
}

