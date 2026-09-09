#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

#include <string>

enum e_type {
  CHAR,
  INT,
  FLOAT,
  DOUBLE,
  PSEUDO,
  INVALID
};

class ScalarConverter
{
    public:
        static void  convert(const std::string& literal);
    
    private:
        ScalarConverter();
        ScalarConverter(const ScalarConverter& other);
        ScalarConverter&  operator=(const ScalarConverter& other);
        ~ScalarConverter();
};

#endif
