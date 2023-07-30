#ifndef _F3_H
#define _F3_H

#include "Benchmarks.h"

class F3 : public Benchmarks
{
public:
  F3( uint );
  ~F3();

  double compute(const vDouble, const uint);

};

#endif
