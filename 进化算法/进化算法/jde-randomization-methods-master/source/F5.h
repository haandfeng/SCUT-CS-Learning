#ifndef _F5_H
#define _F5_H

#include "Benchmarks.h"

class F5 : public Benchmarks
{
public:
  F5( uint );
  ~F5();

  double compute(const vDouble, const uint);
};

#endif
