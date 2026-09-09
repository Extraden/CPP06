#include <iostream>
#include <string>
#include "ScalarConverter.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout
        << "Wrong arguments!\n"
        << "Usage:\n"
        << "./convert 42\n";
        return (0);
    }

    ScalarConverter::convert(argv[1]);
    return (0);
}
