#include <iostream>
#include <stdint.h>
#include "Data.hpp"
#include "Serializer.hpp"

int	main()
{
  uintptr_t ptr = 0;
  Data data;
  data.value = 42;

  std::cout << "Initial address: " << &data << "\n"
            << "Initial value: " << data.value << "\n";

  ptr = Serializer::serialize(&data);

  Data  *result = Serializer::deserialize(ptr);

  std::cout << "Result address: " << result << "\n"
            << "Result value: " << result->value << "\n";

  if (&data == result)
    std::cout << "Addresses are equal\n";
  else
   std::cout << "Addresses are not equal\n";
	return 0;
}
