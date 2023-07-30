#ifndef _F2_H
#define _F2_H

#include "Benchmarks.h"

class F2 : public Benchmarks
{
public:
  F2( uint );
  ~F2();

  double compute(const vDouble, const uint);

};

#endif
