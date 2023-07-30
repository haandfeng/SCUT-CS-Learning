#ifndef _BENCHMARKS_H
#define _BENCHMARKS_H

#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>

typedef std::vector<double> vDouble;
#define PI (3.141592653589793238462643383279)

class Benchmarks
{
protected:

  double x_min;
  double x_max;

  uint n_dim;
  uint ID;

public:

  Benchmarks();
  virtual ~Benchmarks();

  /*
   * vDouble represents the gene
   * uint start point of the individual (initial point)
   */
  virtual double compute(const vDouble, const uint){
    /* emtpy */
  };

  virtual double compute(const double *, const uint){
    /* emtpy */
  };

  double getMin();
  double getMax();
  uint getID();

  void setMin( const double );
  void setMax( const double );
  void setDim( const uint );

  void check( const uint );

};

#endif
