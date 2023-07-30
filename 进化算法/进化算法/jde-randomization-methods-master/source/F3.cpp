#include "F3.h"

#include <fstream>
#include <iostream>

F3::F3(uint _dim):Benchmarks()
{
  n_dim = _dim;

  ID = 3;
  x_min = -600.0;
  x_max = +600.0;
}

F3::~F3(){
  /* empty */
}

double F3::compute(const vDouble gen, const uint ip){
  	/* Defining fitness function - Griewank's function
	   Dimensions: d
	   Domain: x ∈ [-600.0, 600.0]
	   Global minimum: (0, ..., 0)
	*/
	double aux, aux1, aux2 = 0;

    aux = aux1 = 0;
    aux2 = 1;
    for(uint j = 0; j < n_dim; j++) {
    	aux1 = aux1 + pow((gen[j + ip]),(double)2);
    	aux2 = aux2 * cos((((gen[j + ip])/sqrt((double)(j+1)))*M_PI)/180);
    }
    aux = (1/(double)4000) * aux1 - aux2 + 1;

    return aux;
}


