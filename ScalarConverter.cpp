#include "ScalarConverter.hpp"
#include <cstddef>
#include <iostream>
#include <limits>
#include <cerrno>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <cctype>

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
  if (literal.empty())
    return false;

  size_t i = 0;
  if (literal[0] == '+' || literal[0] == '-')
    ++i;

  if (i == literal.length())
    return false;

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
  if (literal.empty())
    return false;

  bool hasDigit = false;
  int points = 0;
  for (size_t i = 0; i < literal.length(); ++i)
  {
    if (literal[i] == '.')
      points++;
    else if (std::isdigit(literal[i]))
      hasDigit = true;
  }
  if (points != 1 || !hasDigit)
    return false;

  size_t i = 0;

  if (literal[0] == '+' || literal[0] == '-')
    ++i;

  while (i < literal.length())
  {
    if (!(std::isdigit(literal[i])) && (literal[i] != '.'))
        return false;
    ++i;
  }
  return true;
}

bool  isFloat(const std::string& literal)
{
  if (literal.empty())
    return false;

  if (literal[literal.length() - 1] != 'f')
    return false;

  std::string res = literal.substr(0, literal.length() - 1);

  if (isDouble(res))
    return true;

  return false;
}

e_type  checkType(const std::string& literal)
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

void    handleChar(char c)
{
  std::cout << "char: " << "'" << c << "'" << "\n"
            << "int: " << static_cast<int>(c) << "\n"
            << std::fixed << std::setprecision(1)
            << "float: " << static_cast<float>(c) << "f\n"
            << "double: " << static_cast<double>(c) << "\n";
}

void  handleInt(const std::string& literal)
{
  errno = 0;
  char *end;

  long l = std::strtol(literal.c_str(), &end, 10);
  if (errno == ERANGE || l < std::numeric_limits<int>::min() || l > std::numeric_limits<int>::max())
  {
    std::cout << "char: impossible\n"
            << "int: impossible\n"
            << "float: impossible\n"
            << "double: impossible\n";
  }
  else
  {
    int i = static_cast<int>(l);
    double d = static_cast<double>(i);
    float f = static_cast<float>(i);
    if ((i > std::numeric_limits<char>::max()) || (i < std::numeric_limits<char>::min()))
      std::cout << "char: impossible\n";
    else
    {
      char c = static_cast<char>(i);
      if (std::isprint(static_cast<unsigned char>(c)))
        std::cout << "char: " << "'" << c << "'" << "\n";
      else
        std::cout << "char: Non displayable\n";
    }

  std::cout << "int: " << i << "\n"
          << std::fixed << std::setprecision(1)
          << "float: " << f << "f\n"
          << "double: " << d << "\n";
  }
}

void  handleDouble(const std::string& literal)
{
  char *end;

  double d = std::strtod(literal.c_str(), &end);
  char c = static_cast<char>(d);
  int i = static_cast<int>(d);
  float f = static_cast<float>(d);

  if (std::isprint(static_cast<unsigned char>(c)))
    std::cout << "char: " << "'" << c << "'" << "\n";
  else
    std::cout << "char: Non displayable\n";
  

  std::cout << "int: " << i << "\n"
            << std::fixed
            << "float: " << f << "f\n"
            << "double: " << d << "\n";
}

void  handleFloat(const std::string& literal)
{
  std::string tmp = literal.substr(0, literal.length() - 1);
  std::istringstream iss(tmp);

  float f;
  iss >> f;

  char c = static_cast<char>(f);
  int i = static_cast<int>(f);
  double d = static_cast<double>(f);

  if (std::isprint(static_cast<unsigned char>(c)))
    std::cout << "char: " << "'" << c << "'" << "\n";
  else
    std::cout << "char: Non displayable\n";
  

  std::cout << "int: " << i << "\n"
            << std::fixed
            << "float: " << f << "f\n"
            << "double: " << d << "\n";
}

void  ScalarConverter::convert(const std::string& literal)
{
  e_type type = checkType(literal);

  if (type == PSEUDO)
    handlePseudo(literal);
  else if (type == CHAR)
    handleChar(literal[0]);
  else if (type == INT)
    handleInt(literal);
  else if (type == DOUBLE)
    handleDouble(literal);
  else if (type == FLOAT)
    handleFloat(literal);
  else if (type == INVALID)
    std::cout << "Invalid input\n";
}

