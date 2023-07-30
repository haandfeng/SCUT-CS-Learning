#ifndef __jDE__
#define __jDE__

#include <tuple>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>
#include <cassert>
#include <chrono>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

typedef std::vector<double> vDouble;

class jDE {

private:
  double f_lower;
  double f_upper;
  double T;

  vDouble F;
  vDouble CR;

  vDouble T_F;
  vDouble T_CR;

  uint size;

  std::mt19937 rng;
  gsl_rng *r;
public:
  jDE( uint );
  ~jDE();

  double getFLower();
  double getFUpper();
  double getT();

  void setFLower( const double );
  void setFUpper( const double );
  void setT( const double );

  /* update the F and CR values */
  void update(uint, double &);

  /* print all F values */
  void showF();

  /* print all CR values */
  void showCR();

  /*
   * Reset to default F and CR
   */
  void reset();

  /*
   * Performs a iteration of DE/rand/1/bin using
   * jDE self-adaptation.
   * @params:
   *    - uint: num of dimensions
   *    - uint: pop size
   *    - vector<double> containing the genes(ps x ndim)
   *    - vector<double> to put the new generation
   *    - Benchmarks to check bounds
   */
  void runDE(uint, uint, const vDouble &, vDouble &, const double, const double, uint, double &);

  /*
   * Performs selection on the new offsprings
   * @params:
   *    - uint: num of dimensions
   *    - uint: pop size
   *    - vector<double> containing the genes(ps x ndim)
   *    - vector<double> containing the new genes(ps x ndim)
   *    - vector<double> containing the fitness of previous generation
   *    - vector<double> containing the fitness of new generation
   */
  void selection(uint, uint, vDouble &, const vDouble &, vDouble& fitness, const vDouble & );

  /*
   * This article propose a simple method to constrained handle:
   *
   * J. Zhang and A. C. Sanderson, "JADE: Adaptive differential evolution
   * with optional external archive," IEEE Tran. Evol. Comput., vol. 13,
   * no. 5, pp. 945–958, 2009.
   *
   * @params:
   *    - double: c[i] trial vector ith dimensions to check bounds
   *    - cdouble: parent[i], ith dimension of the parent
   *    - cdouble: x_min, lower bound
   *    - cdouble: x_max, upper bound
   */
  double bound_handle(double, const double, const double, const double);


  /*
	Chaotic maps
  */

  double logisticMap(double randomNum, double r);

  double remap(double from, double fromMin, double fromMax, double toMin,  double toMax);
};

#endif
