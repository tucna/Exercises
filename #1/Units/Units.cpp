#include <iostream>

#include "Value.h"
#include "Test.h"

int main()
{
  Test test;

  constexpr Speed speed = Length{ 2.0 } / Time{ 5.0 };
  constexpr Momentum momentum = Force{ 30.0 } * Time{ 3.0 };

  Force force = 30.0_N;
  Time time = 3.0_s;
  Momentum momentumDifferent = force * time;

  test.applyMomentum(momentum);
}
