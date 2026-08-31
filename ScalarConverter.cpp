#include "ScalarConverter.hpp"
#include <iostream>
#include <limits>

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& other)
{
  (void) other;
}

ScalarConverter&  ScalarConverter::operator=(const ScalarConverter& other)
{
  (void) other;
  return *this;
}

ScalarConverter::~ScalarConverter() {}

e_type  ScalarConverter::checkType(const std::string& literal)
{
  if (literal.length() == 1 && !isdigit(literal[0]))
    return CHAR;
  else if (literal == "+inf" || literal == "-inf" ||
          literal == "+inff" || literal == "-inff" || 
          literal == "nan" || literal == "nanf")
    return PSEUDO;
  else
    return INVALID;
}

void  handlePseudo(const std::string& literal)
{
  double value = 0;

  if (literal == "+inf" || literal == "+inff")
    value = std::numeric_limits<double>::infinity();
  else if (literal == "-inf" || literal == "-inff")
    value = -std::numeric_limits<double>::infinity();
  else if (literal == "nan" || literal == "nanf")
    value = std::numeric_limits<double>::quiet_NaN();
  std::cout << "char: impossible\n"
            << "int: impossible\n"
            << "float: " << value << "f\n"
            << "double: " << value << "\n";
}

//void  printOuput()

void  ScalarConverter::convert(const std::string& literal)
{
  e_type type = ScalarConverter::checkType(literal);

  if (type == PSEUDO)
  {
    handlePseudo(literal);
    return;
  }
  return;
}

