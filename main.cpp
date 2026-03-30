#include <iostream>

int main(int argc, char *argv[])
{
    (void) argv;
    if (argc != 2)
    {
        std::cout
        << "Wrong arguments!\n"
        << "Usage:\n"
        << "./convert 42f\n";
        return (0);
    }
    return (0);
}