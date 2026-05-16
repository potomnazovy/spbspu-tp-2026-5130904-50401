#ifndef CLI_HPP
#define CLI_HPP
#include "commands.hpp"

namespace vasyakin
{
  struct command
  {
    static std::vector< Polygon >* all_polygons;
    command() = default;
  };

  std::istream& operator>>(std::istream& in, command&);
  void readData(std::istream& in, std::vector< Polygon >& all_polygons);
}

#endif
