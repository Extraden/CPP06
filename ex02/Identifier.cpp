#include "Identifier.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>
#include <iostream>

Base* generate(void)
{
  int choice = std::rand() % 3;

  switch (choice)
  {
    case 0:
      return new A;
    case 1:
      return new B;
    case 2:
      return new C;
    default:
      return NULL;
  }
}

void identify(Base* p)
{
  if (dynamic_cast<A *>(p))
    std::cout << "Class A\n";
  else if (dynamic_cast<B *>(p))
    std::cout << "Class B\n";
  else if (dynamic_cast<C *>(p))
    std::cout << "Class C\n";
  else
   std::cout << "Unknown Class\n";
}

void identify(Base& p)
{
  try
  {
    (void) dynamic_cast<A&>(p);
    std::cout << "Class A\n";
    return;
  }
  catch (...) {}

  try {
    (void) dynamic_cast<B&>(p);
    std::cout << "Class B\n";
  }
  catch (...) {}

  try {
    (void)dynamic_cast<C&>(p);
    std::cout << "Class C\n";
  } 
  catch (...) {}
}
