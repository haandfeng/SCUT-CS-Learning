#ifndef _F7_H
#define _F7_H

#include "Benchmarks.h"

class F7 : public Benchmarks
{
public:
  F7( uint );
  ~F7();

  double compute(const vDouble, const uint);
};

#endif
