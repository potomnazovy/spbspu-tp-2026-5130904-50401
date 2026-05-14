#ifndef UTILS_HPP
#define UTILS_HPP
#include <iostream>
#include <string>
#include <iomanip>

namespace vasyakin
{
  struct DataStruct
  {
    char key1;
    std::pair< long long, unsigned long long > key2;
    std::string key3;
  };

  struct DelimeterIO
  {
    char exp;
  };

  struct CharIO
  {
    char& ref;
  };

  struct RatioIO
  {
    std::pair< long long, unsigned long long >& ref;
  };

  struct StringIO
  {
    std::string& ref;
  };

  struct LabelIO
  {
    std::string& ref;
  };
}

#endif
