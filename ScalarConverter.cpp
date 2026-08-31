#include "ScalarConverter.hpp"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <limits>
#include <iomanip>
#include <cstdlib>

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

bool  isInt(const std::string& literal)
{
  int i = 0;
  if (literal[0] == '+' || literal[0] == '-')
    ++i;
  while (i < literal.length())
  {
    if (!(std::isdigit(literal[i])))
      return false;
    ++i;
  }
  return true;
}

bool  isDouble(const std::string& literal)
{
  bool hasPoint = false;
  int i = 0;

  if (literal[0] == '+' || literal[0] == '-')
    ++i;

  ssize_t pointIndex = literal.find('.');
  
  while (i < literal.length())
  {
    if (literal[i] == '.')
    {
      if (hasPoint == true)
        return false;
      else
        hasPoint = true;
    }
    if (std::isdigit(literal[i]))

    ++i;
  }
  return true;
}

bool  isFloat(const std::string& literal)
{
  int i = 0;
  if (literal[0] == '+' || literal[0] == '-')
    ++i;
  while (i < literal.length())
  {
    if (!(std::isdigit(literal[i])))
      return false;
    ++i;
  }
  return true;
}

e_type  ScalarConverter::checkType(const std::string& literal)
{
  if (literal.length() == 1 && !isdigit(literal[0]))
    return CHAR;
  else if (literal == "+inf" || literal == "-inf" ||
          literal == "+inff" || literal == "-inff" || 
          literal == "nan" || literal == "nanf")
    return PSEUDO;
  else if (isInt(literal))
    return INT;
  else if (isDouble(literal))
    return DOUBLE;
  else if (isFloat(literal))
    return FLOAT;
  else
    return INVALID;
}

void  ScalarConverter::handlePseudo(const std::string& literal)
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

void    ScalarConverter::handleChar(char c)
{
  std::cout << "char: " << c << "\n"
            << "int: " << static_cast<int>(c) << "\n"
            << std::fixed << std::setprecision(1)
            << "float: " << static_cast<float>(c) << "f\n"
            << "double: " << static_cast<double>(c) << "\n";
}

void  ScalarConverter::handleNumber(const std::string& literal)
{
  char *end;

  double d = std::strtod(literal.c_str(), &end);
  char c = static_cast<char>(d);
  int i = static_cast<int>(d);
  float f = static_cast<float>(d);

  if (std::isprint(c))
    std::cout << "char: " << c << "\n";
  else
    std::cout << "Non displayable\n";
  

  std::cout << "int: " << i << "\n"
            << std::fixed << std::setprecision(1)
            << "float: " << f << "f\n"
            << "double: " << d << "\n";
}

void  ScalarConverter::convert(const std::string& literal)
{
  e_type type = ScalarConverter::checkType(literal);

  if (type == PSEUDO)
  {
    handlePseudo(literal);
    return;
  }
  else if (type == CHAR)
    handleChar(literal[0]);
  else if (type == NUMBER)
    handleNumber(literal);
  return;
}

