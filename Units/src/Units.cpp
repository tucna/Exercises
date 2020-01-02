#include <iostream>

#include "Value.h"

int main()
{
  constexpr Speed speed = Length{ 2.0 } / Time{ 5.0 };
  constexpr Momentum momentum_1 = Force{ 30.0 } * Time{ 3.0 };

  Force force = 30.0_N;
  Time time = 3.0_s;
  Momentum momentum_2 = force * time;

  Length length = 5.0_mm;

  std::cout << length << "\n";

  return 0;
}
