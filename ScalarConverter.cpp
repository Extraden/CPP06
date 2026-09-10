#include "ScalarConverter.hpp"
#include <cstddef>
#include <iostream>
#include <limits>
#include <cerrno>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <sstream>

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

std::string formatFloating(double num)
{
  std::ostringstream oss;
   
  if (std::floor(num) == num)
    oss << std::fixed << std::setprecision(1);

  oss << num;
  return oss.str();
}

std::string formatFloating(float num)
{
  std::ostringstream oss;
   
  if (std::floor(num) == num)
    oss << std::fixed << std::setprecision(1);

  oss << num;
  return oss.str();
}

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
            << "float: " << formatFloating(static_cast<float>(c)) << "f\n"
            << "double: " << formatFloating(static_cast<double>(c)) << "\n";
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
          << "float: " << formatFloating(f) << "f\n"
          << "double: " << formatFloating(d) << "\n";
  }
}

void  handleDouble(const std::string& literal)
{
  char *end;

  errno = 0;
  double d = std::strtod(literal.c_str(), &end);

  if (errno == ERANGE && (d == HUGE_VAL || d == -HUGE_VAL))
  {
    std::cout << "char: impossible\n"
            << "int: impossible\n"
            << "float: impossible\n"
            << "double: impossible\n";
    return;
  }
  else
  {
    if ((d >= std::numeric_limits<char>::max() + 1.0) || (d <= std::numeric_limits<char>::min() - 1.0))
      std::cout << "char: impossible\n";
    else
    {
      char c = static_cast<char>(d);
      if (std::isprint(static_cast<unsigned char>(c)))
        std::cout << "char: " << "'" << c << "'" << "\n";
      else
        std::cout << "char: Non displayable\n";
    }
    if ((d >= std::numeric_limits<int>::max() + 1.0) || (d <= std::numeric_limits<int>::min() - 1.0))
    {
      std::cout << "int: impossible\n";
    }
    else
    {
      int i = static_cast<int>(d);
      std::cout << "int: " << i << "\n";
    }
    if (d > std::numeric_limits<float>::max() || d < -std::numeric_limits<float>::max())
    {
      std::cout << "float: impossible\n";
    }
    else
    {
      float f = static_cast<float>(d);
      std::cout << "float: " << formatFloating(f) << "f\n";
    }

    std::cout << "double: " << formatFloating(d) << "\n";
  }
}

void  handleFloat(const std::string& literal)
{
  std::string tmp = literal.substr(0, literal.length() - 1);

  char *end;
  errno = 0;
  double parsed = std::strtod(tmp.c_str(), &end);


  if (errno == ERANGE && (parsed == HUGE_VAL || parsed == -HUGE_VAL))
  {
    std::cout << "char: impossible\n"
            << "int: impossible\n"
            << "float: impossible\n"
            << "double: impossible\n";
    return;
  }
  if (parsed > std::numeric_limits<float>::max() || parsed < -std::numeric_limits<float>::max())
  {
    std::cout << "char: impossible\n"
            << "int: impossible\n"
            << "float: impossible\n"
            << "double: impossible\n";
    return;
  }
  float f = static_cast<float>(parsed);
  if ((f >= std::numeric_limits<char>::max() + 1.0) || (f <= std::numeric_limits<char>::min() - 1.0))
    std::cout << "char: impossible\n";
  else
  {
    char c = static_cast<char>(f);
    if (std::isprint(static_cast<unsigned char>(c)))
      std::cout << "char: " << "'" << c << "'" << "\n";
    else
      std::cout << "char: Non displayable\n";
  }
  if ((f >= std::numeric_limits<int>::max() + 1.0) || (f <= std::numeric_limits<int>::min() - 1.0))
  {
    std::cout << "int: impossible\n";
  }
  else
  {
    int i = static_cast<int>(f);
    std::cout << "int: " << i << "\n";
  }
  double d = static_cast<double>(f);

  std::cout << "float: " << formatFloating(f) << "f\n"
            << "double: " << formatFloating(d) << "\n";
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

