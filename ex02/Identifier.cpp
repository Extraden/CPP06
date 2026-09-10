#include "Identifier.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>
#include <iostream>

Base* generate(void)
{
  int choice = std::rand() % 3;
  std::cout << choice;

  switch (choice)
  {
    case 0:
      return new A;
    case 1:
      return new B;
    case 2:
      return new C;
  }
  return NULL;
}
