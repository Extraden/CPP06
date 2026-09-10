#include "Identifier.hpp"
#include <cstdlib>

int	main()
{
  std::srand(42);

  Base *result = generate();
  identify(result);
	return 0;
}
