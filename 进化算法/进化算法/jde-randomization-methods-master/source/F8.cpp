#include "F8.h"

#include <fstream>
#include <iostream>

F8::F8(uint _dim):Benchmarks()
{
  n_dim = _dim;

  ID = 8;
  x_min = -5;
  x_max = +10;
}

F8::~F8(){
  /* empty */
}


double F8::compute(const vDouble gen, const uint ip){
  	/* Defining fitness function - Zakharov function 
	   Dimensions: d
	   Domain: x ∈ [-5, 10]
	   known_optimal = 0
	*/	

  double result = 0.0, aux = 0.0, aux1 = 0.0;

  for (uint j = 0; j< n_dim; j++){
      aux = aux + pow(gen[j + ip],2.0);
      aux1 = aux1+0.5*j*gen[j + ip];
  }

  result = ( aux+pow(aux1,2.0)+pow(aux1,4.0) );

  return result;
}

