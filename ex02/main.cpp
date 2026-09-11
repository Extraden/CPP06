#include "Identifier.hpp"
#include <cstdlib>

int	main()
{
  std::srand(50);

  Base *ptr1 = generate();

  identify(ptr1);
  identify(*ptr1);

  Base *ptr2 = generate();

  identify(ptr2);
  identify(*ptr2);

  delete ptr1;
  delete ptr2;
	return 0;
}
