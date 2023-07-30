#ifndef _F1_H
#define _F1_H

#include "Benchmarks.h"

class F1 : public Benchmarks
{
public:
  F1( uint );
  ~F1();

  double compute(const vDouble, const uint);

};

#endif
