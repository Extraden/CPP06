#include <iostream>
#include <stdint.h>
#include "Serializer.hpp"

int	main()
{
  uintptr_t ptr;
  Data *data = new Data;

  std::cout << data << "\n";

  ptr = Serializer::serialize(data);

  Data  *result = Serializer::deserialize(ptr);

  std::cout << result << "\n";
	return 0;
}
