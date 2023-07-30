#ifndef _F8_H
#define _F8_H

#include "Benchmarks.h"

class F8 : public Benchmarks
{
public:
  F8( uint );
  ~F8();

  double compute(const vDouble, const uint);

};

#endif
