#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "utils.hpp"

namespace vasyakin
{
  void area(std::istream& in, std::ostream& out, std::vector< Polygon >& poly);
  void count(std::istream& in, std::ostream& out, std::vector< Polygon >& poly);
  void max(std::istream& in, std::ostream& out, std::vector< Polygon >& poly);
  void min(std::istream& in, std::ostream& out, std::vector< Polygon >& poly);
  void rects(std::istream& in, std::ostream& out, std::vector< Polygon >& poly);
  void perms(std::istream& in, std::ostream& out, std::vector< Polygon >& poly);
}

#endif
