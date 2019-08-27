#include "pch.h"

#include <iostream>

#include "Value.h"
#include "Test.h"

int main()
{
  Test test;
  Momentum momentum{ 13.75 };

  test.applyMomentum(momentum);

  std::cout << "Hello World!\n";
}
