#include "Benchmarks.h"

Benchmarks::Benchmarks(){
  n_dim = 100;
  x_min = -100.0;
  x_max = +100.0;
}


Benchmarks::~Benchmarks(){
  /* emtpy */
}

double Benchmarks::getMin(){
  return x_min;
}

double Benchmarks::getMax(){
  return x_max;
}

uint Benchmarks::getID(){
  return ID;
}

void Benchmarks::setMin( const double _min ){
  x_min = _min;
}

void Benchmarks::setMax( const double _max ){
  x_max = _max;
}

void Benchmarks::setDim( const uint _dim ){
  n_dim = _dim;
}

void Benchmarks::check( const uint nx ){
  if(!(nx==2 or nx==5 or nx==10 or nx==20 or nx==30 or nx==50 or nx==100)){
    printf("\nError: Rotation matrix are only defined for D = 2,5,10,20,30,50,100.\n");
    exit(-1);
  }
}
