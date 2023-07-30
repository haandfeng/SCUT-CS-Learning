#include "F1.h"

#include <fstream>
#include <iostream>

F1::F1(uint _dim):Benchmarks()
{
  n_dim = _dim;

  ID = 1;
  x_min = -100.0;
  x_max = +100.0;
}

F1::~F1(){
  /* empty */
}

double F1::compute(const vDouble gen, const uint ip){

  /* Defining fitness function - Schaffer's function
     Dimensions: d
     Domain: x ∈ [-100.0, 100.0]
     Global minimum: (0, ..., 0)
  */

  double aux = 0, aux1;

  aux1 = 0;
  for(uint j = 0; j < n_dim; j++) {
    aux = aux + (pow(gen[j + ip],(double)2));
  }

  aux = pow(aux,(double)0.25);

  for(uint j = 0; j < n_dim; j++) {
    aux1 = aux1 + (pow(gen[j + ip],(double)2));
  }

  aux1 = pow(aux1,(double)0.1);
  aux1 = pow(sin(50*aux1),(double)2) + 1.0;

  return aux*aux1;
}

