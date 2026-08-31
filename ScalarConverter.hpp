#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

#include <string>

enum e_type {
  CHAR,
  NUMBER,
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

        static  e_type  checkType(const std::string& literal);
        static  void    handlePseudo(const std::string& literal);
        static  void    handleChar(char c);
        static  void    handleNumber(const std::string& literal);
};

#endif
