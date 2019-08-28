#include <iostream>

#include "Value.h"

int main()
{
  constexpr Speed speed = Length{ 2.0 } / Time{ 5.0 };
  constexpr Momentum momentum = Force{ 30.0 } * Time{ 3.0 };

  Force force = 30.0_N;
  Time time = 3.0_s;
  Momentum momentumDifferent = force * time;

  Length m = 5.0_mm;

  std::cout << m << "\n";

  return 0;
}
