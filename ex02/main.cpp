#include "Identifier.hpp"
#include <cstdlib>

int	main()
{
  std::srand(42);

  Base *ptr = generate();

  identify(ptr);
  identify(*ptr);

  delete ptr;
	return 0;
}
