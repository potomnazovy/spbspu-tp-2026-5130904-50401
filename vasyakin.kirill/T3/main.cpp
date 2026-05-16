#include <iostream>
#include <fstream>
#include <limits>
#include "commands.hpp"
#include "cli.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Too much or no file" << '\n';
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file)
  {
    std::cerr << "Cannot open file\n";
    return 1;
  }

  std::vector< vasyakin::Polygon > all_polygons;
  vasyakin::readData(file, all_polygons);

  vasyakin::command::all_polygons = &all_polygons;

  std::vector< vasyakin::command > v;
  std::copy(std::istream_iterator< vasyakin::command >{std::cin},
    std::istream_iterator< vasyakin::command >{},
    std::back_inserter(v));

  return 0;
}
