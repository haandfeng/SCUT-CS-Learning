#ifndef _F6_H
#define _F6_H

#include "Benchmarks.h"

class F6 : public Benchmarks
{
public:
  F6( uint );
  ~F6();

  double compute(const vDouble, const uint);
};

#endif
